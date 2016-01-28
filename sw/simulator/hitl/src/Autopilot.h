/*
 * Copyright (C) 2015 Michal Podhradsky, michal.podhradsky@aggiemail.usu.edu
 * Utah State University, http://aggieair.usu.edu/
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
/**
 * @file Autopilot.h
 *
 * HITL demo version - Autopilot RX class
 *
 * @author Michal Podhradsky <michal.podhradsky@aggiemail.usu.edu>
 */
#ifndef SRC_AUTOPILOT_H_
#define SRC_AUTOPILOT_H_

#include <stdio.h>     // Standard input/output definitions
#include <string.h>    // String function definitions

#include <boost/asio/serial_port.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

#include <iomanip>
#include <fstream>

#include "MsgConfig.h"
#include "MsgPacket.h"
#include "AutopilotData.h"
#include "LogTime.h"
#include "Lidar.h"

using namespace std;

#define DEBUG_AP 0
#define LOG_BINARY 0

class Autopilot
{
private:
  MsgPacket data_packet_;
  AutopilotData data_;

  Lidar lidar_;

  boost::asio::serial_port& port_;
  char buffer_[BUF_SIZE] = { };
  uint8_t work_;  // flag
  bool new_data_;
  boost::mutex datalock_;  // mutex
  timeval start_time_;

#if LOG_BINARY
  ofstream file_;
  string ext_ = "bin";
  string filename_;
#endif

  /**
   * Calculate checksum per Xgear documentation
   * @param data
   * @param data_len
   * @return
   */
  uint16_t calculate_checksum(uint8_t* data, uint16_t data_len)
  {
    uint8_t byte1 = 0;
    uint8_t byte2 = 0;
    for (int x = 0; x < data_len; ++x) {
      byte1 += data[x];
      byte2 += byte1;
    }
    return (byte1 << 8) + byte2;
  }

  /**
   * Attempt to read data from the serial port
   */
  void read_data(void)
  {
    int length = boost::asio::read(port_,
        boost::asio::buffer((char*) buffer_, sizeof(buffer_)));

    if (length == -1) {
      printf("Error reading from serial port\n");
      return;
    } else if (length == 0) {
      return;
    } else {
      // parse individual bytes
      for (int i = 0; i < length; i++) {
        parse_message(buffer_[i]);
      }
#if LOG_BINARY
      //save to file
      file_.write(buffer_, length * sizeof(char));
      file_.flush();
#endif
    }
  }

  /**
   * Parse message
   */
  void parse_message(uint8_t c)
  {
    static uint16_t rx_chksum, calc_chksum;

    switch (data_packet_.status) {
      case MsgSync0:  // SYNC 0 = 0xBE, idx=0
        data_packet_.msg_idx = 0;
        //cout << std::hex << (int)c << endl;
        if (c == HITL_SYNC0) {
          //cout << "SYNC0 OK" << endl;
          data_packet_.msg_buf[data_packet_.msg_idx] = c;
          data_packet_.msg_idx++;
          data_packet_.status = MsgSync1;
        } else {
          data_packet_.hdr_error++;
        }
        break;
      case MsgSync1:  // SYNC 1 = 0xEF, idx=1
        //cout << std::hex << (int)c << endl;
        if (c == HITL_SYNC1) {
          //cout << "SYNC1 OK" << endl;
          data_packet_.msg_buf[data_packet_.msg_idx] = c;
          data_packet_.msg_idx++;
          data_packet_.status = MsgType;
        } else {
          //cout << "SYNC1 ERR" << endl;
          data_packet_.status = MsgSync0;
          data_packet_.hdr_error++;
        }
        break;
      case MsgType:  // TYPE=0, idx=2
        //cout << std::hex << (int)c << endl;
        if (c == HITL_MSG_TYPE) {
          //cout << "MSG_TYPE OK" << endl;
          data_packet_.msg_buf[data_packet_.msg_idx] = c;
          data_packet_.msg_idx++;
          data_packet_.status = MsgSize;
        } else {
          //cout << "MSG_TYPE ERR" << endl;
          data_packet_.status = MsgSync0;
          data_packet_.hdr_error++;
        }
        break;
      case MsgSize:  // SIZE = 167, idx=3,4
        data_packet_.msg_buf[data_packet_.msg_idx] = c;
        data_packet_.msg_idx++;
        if (data_packet_.msg_idx == 5) {
          data_packet_.datalength =
              (uint16_t) (data_packet_.msg_buf[data_packet_.msg_idx - 2] << 8
                  | data_packet_.msg_buf[data_packet_.msg_idx - 1]);
          data_packet_.status = MsgHdrChksum;
        }
        break;
      case MsgHdrChksum:  // HDR CHKSUM, idx=5,6
        data_packet_.msg_buf[data_packet_.msg_idx] = c;
        data_packet_.msg_idx++;
        if (data_packet_.msg_idx == 7) {
          // FIXME: memcopy reverses byte order on Ubuntu 14.04 64-bit
          //memcpy(&rx_chksum, &data_packet_.msg_buf[data_packet_.msg_idx - 2],sizeof(uint16_t));
          rx_chksum = (data_packet_.msg_buf[data_packet_.msg_idx-2]<<8)+data_packet_.msg_buf[data_packet_.msg_idx-1];
          calc_chksum = calculate_checksum(data_packet_.msg_buf+2,(uint16_t) (HITL_HEADER_LENGTH - 4));

          if (rx_chksum == calc_chksum) {
            // header checksum OK, proceed to reading data
            if (DEBUG_AP) cout << "HDR_CHKSUM OK" << endl;
            data_packet_.msg_idx = 0;
            data_packet_.status = MsgData;
          } else {
            // invalid checksum
        	  if (DEBUG_AP) cout << "HDR CHKSUM ERR" << endl;
            data_packet_.status = MsgSync0;
            data_packet_.chksm_error++;
          }
        }
        break;
      case MsgData:

        data_packet_.msg_buf[data_packet_.msg_idx] = c;
        data_packet_.msg_idx++;

        if (data_packet_.msg_idx == (data_packet_.datalength + CHK_LEN)) {
          // FIXME: memcopy reverses byte order on Ubuntu 14.04 64-bit
          //memcpy(&rx_chksum, &data_packet_.msg_buf[data_packet_.msg_idx - 2],sizeof(uint16_t));
          rx_chksum = (data_packet_.msg_buf[data_packet_.msg_idx-2]<<8)+data_packet_.msg_buf[data_packet_.msg_idx-1];
          calc_chksum = calculate_checksum(data_packet_.msg_buf,data_packet_.datalength);
          if (rx_chksum == calc_chksum) {
            // header checksum OK, proceed to reading msg
            data_.msg_cnt++;
            if (DEBUG_AP) cout << "DATA_CHKSUM OK" << endl;
            read_message();
          } else {
            // invalid checksum
        	if (DEBUG_AP) cout << "DATA_CHKSUM ERR" << endl;
            data_packet_.chksm_error++;
          }
          data_packet_.status = MsgSync0;
        }
        break;
      default:
        data_packet_.status = MsgSync0;
        data_packet_.msg_idx = 0;
        break;
    }

  }

  /**
   * Read message
   * we have a packet with datalength and a buffer
   */
  void read_message(void)
  {
    datalock_.lock();
    uint16_t idx = 0;

    // timestamp
    memcpy(&data_.time_startup, &data_packet_.msg_buf[idx], sizeof(float));
    idx += sizeof(float);

    // yaw, pitch, roll
    memcpy(&data_.YawPitchRoll, &data_packet_.msg_buf[idx], 3 * sizeof(float));
    idx += 3 * sizeof(float);

    // AngularRate
    memcpy(&data_.angularRate, &data_packet_.msg_buf[idx], 3 * sizeof(float));
    idx += 3 * sizeof(float);

    // Position
    memcpy(&data_.position, &data_packet_.msg_buf[idx], 3 * sizeof(double));
    idx += 3 * sizeof(double);

    // Velocity
    memcpy(&data_.velocity_NED, &data_packet_.msg_buf[idx], 3 * sizeof(float));
    idx += 3 * sizeof(float);

    // Accel
    memcpy(&data_.accel, &data_packet_.msg_buf[idx], 3 * sizeof(float));
    idx += 3 * sizeof(float);

    // Tow
    memcpy(&data_.tow, &data_packet_.msg_buf[idx], sizeof(uint32_t));
    idx += sizeof(uint32_t);

    // NumSats
    data_.numSats = data_packet_.msg_buf[idx];
    idx++;

    // GPS Fix
    data_.gpsFix = data_packet_.msg_buf[idx];
    idx++;

    // PosU
    memcpy(&data_.posU, &data_packet_.msg_buf[idx], 3 * sizeof(float));
    idx += 3 * sizeof(float);

    // VelU
    memcpy(&data_.velU, &data_packet_.msg_buf[idx], sizeof(float));
    idx += sizeof(float);

    // LinearAccel Body
    memcpy(&data_.linAccelBody, &data_packet_.msg_buf[idx], 3 * sizeof(float));
    idx += 3 * sizeof(float);

    // YprU
    memcpy(&data_.yprU, &data_packet_.msg_buf[idx], 3 * sizeof(float));
    idx += 3 * sizeof(float);

    // INS status
    memcpy(&data_.insStatus, &data_packet_.msg_buf[idx], sizeof(uint16_t));
    idx += sizeof(uint16_t);

    // VelBody
    memcpy(&data_.velBody, &data_packet_.msg_buf[idx], 3 * sizeof(float));
    idx += 3 * sizeof(float);

    // Ap time
    memcpy(&data_.ap_time, &data_packet_.msg_buf[idx], sizeof(float));
    idx += sizeof(float);

    // COMMANDS_NB
    data_.actuators_nb = data_packet_.msg_buf[idx];
    idx++;

    // CMD_THROTTLE / Servo#0, int16
    memcpy(&data_.cmd_throttle, &data_packet_.msg_buf[idx], sizeof(int16_t));
    idx += sizeof(uint16_t);
    data_.cmd_throttle_norm = ((double) data_.cmd_throttle / MAX_PPRZ);
    data_.actuators[0] = data_.cmd_throttle;

    // CMD_ROLL / Servo#1, int16
    memcpy(&data_.cmd_roll, &data_packet_.msg_buf[idx], sizeof(int16_t));
    idx += sizeof(uint16_t);
    data_.cmd_roll_norm = ((double) data_.cmd_roll / MAX_PPRZ);
    data_.actuators[1] = data_.cmd_roll;

    // CMD_PITCH / Servo#2, int16
    memcpy(&data_.cmd_pitch, &data_packet_.msg_buf[idx], sizeof(int16_t));
    idx += sizeof(uint16_t);
    data_.cmd_pitch_norm = ((double) data_.cmd_pitch / MAX_PPRZ);
    data_.actuators[2] = data_.cmd_pitch;

    // CMD_YAW / Servo#3, int16
    memcpy(&data_.cmd_yaw, &data_packet_.msg_buf[idx], sizeof(int16_t));
    idx += sizeof(uint16_t);
    data_.cmd_yaw_norm = ((double) data_.cmd_yaw / MAX_PPRZ);
    data_.actuators[3] = data_.cmd_yaw;

    // CMD_FLAPS / Servo#4, int16
    memcpy(&data_.cmd_flaps, &data_packet_.msg_buf[idx], sizeof(int16_t));
    idx += sizeof(uint16_t);
    data_.cmd_flaps_norm = ((double) data_.cmd_flaps / MAX_PPRZ);
    data_.actuators[4] = data_.cmd_flaps;

    // CMD_DUMMY / Servo#5, int16
    memcpy(&data_.cmd_dummy, &data_packet_.msg_buf[idx], sizeof(int16_t));
    idx += sizeof(uint16_t);
    data_.cmd_dummy_norm = ((double) data_.cmd_dummy / MAX_PPRZ);
    data_.actuators[5] = data_.cmd_dummy;

    // Alpha
    memcpy(&data_.alpha, &data_packet_.msg_buf[idx], sizeof(float));
    idx += sizeof(float);

    // Beta
    memcpy(&data_.beta, &data_packet_.msg_buf[idx], sizeof(float));
    idx += sizeof(float);

    // airspeed
    memcpy(&data_.airspeed, &data_packet_.msg_buf[idx], sizeof(float));
    idx += sizeof(float);

    // ap_settings
    memcpy(&data_.ap_settings, &data_packet_.msg_buf[idx], sizeof(uint16_t));
    idx += sizeof(uint16_t);

    // scale final motor commands to 0-1 for feeding the fdm
    for (uint8_t i = 0; i < ACTUATORS_NB; i++) {
      data_.commands[i] = (double) data_.actuators[i] / MAX_PPRZ;
    }

    new_data_ = true;  // mew data arrived
    datalock_.unlock();

#if DEBUG_AP
    cout << LogTime::getTimeSinceStart(start_time_) << ", cmd_val:";
    for (int k = 0; k < data_.actuators_nb; k++) {
      cout << data_.commands[k] << ", ";
    }
    cout << ", cnt: " << data_.msg_cnt << ", hdr errors: "
        << data_packet_.hdr_error << ", chck err: " << data_packet_.chksm_error
        << ", cmd#: " << (int) data_.actuators_nb;
    cout << endl;
#endif
  }

public:
  Autopilot(boost::asio::serial_port& port_n, timeval start_t) :
      port_(port_n)
  {
    start_time_ = start_t;
    work_ = 1;
    data_packet_ = MsgPacket();
    data_ = AutopilotData();
    lidar_ = Lidar();
    new_data_ = false;

#if LOG_BINARY
    // Open Binary file
    filename_ = LogTime::get() + "." + ext_;
    cout << "Autopilot: Opening " << filename_ << endl;
    try {
      file_.open(filename_.c_str());
    } catch (const std::exception& e) {
      std::cout << "Autopilot: Exception: " << e.what() << "\n";
      exit(-1);
    }
#endif

    std::cout << "Binding autopilot \n";
    boost::thread autothread(boost::bind(&Autopilot::workerFunc, this));
  }

  /**
   * Destructor - important to close the file
   */
  ~Autopilot()
  {
#if LOG_BINARY
    file_.close();
#endif
  }

  void workerFunc()
  {
    std::cout << "AP Thread: Starting to work \n";
    while (work_) {
      read_data();
    }
  }

  /**
   * Sends lidar data to the AP
   */
  void sendLidarData()
  {
    lidar_.getLidarData();
    int length_write = boost::asio::write(port_,
        boost::asio::buffer((char*) lidar_.buffer, lidar_.getIdx()));
    (void)length_write;
    //cout << "Lidar sent " << length_write << " bytes." << endl;
  }

  /**
   * Send fake Isaac status packet
   */
  void sendIsaacStatus()
  {
    lidar_.getIsaacData();
    int length_write = boost::asio::write(port_,
        boost::asio::buffer((char*) lidar_.buffer, lidar_.getIdx()));
    (void)length_write;
    //cout << "Isaac sent " << length_write << " bytes." << endl;
  }

  /**
   * Send fake payload status packet
   */
  void sendPayloadStatus()
  {
    lidar_.getPayloadData();
    int length_write = boost::asio::write(port_,
        boost::asio::buffer((char*) lidar_.buffer, lidar_.getIdx()));
    (void)length_write;
    //cout << "Payload sent " << length_write << " bytes." << endl;
  }

  /**
   * Check whether there are data to send
   * @return True if new data arrived
   */
  bool hasNewData()
  {
    datalock_.lock();
    bool nd = new_data_;
    datalock_.unlock();
    return nd;
  }

  /**
   * get data from autopilot. Also marks new_data false
   * as they were just read.
   * @return AutopilotData - contains all data received
   * from the message.
   */
  AutopilotData getAutopilotData()
  {
    datalock_.lock();
    AutopilotData n_data = data_;
    new_data_ = false;
    datalock_.unlock();
    return n_data;
  }
};

#endif /* SRC_AUTOPILOT_H_ */
