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
 * @file Lidar.h
 *
 * HITL demo version - Autopilot Lidar packet
 *
 * @author Michal Podhradsky <michal.podhradsky@aggiemail.usu.edu>
 */
#ifndef SRC_LIDAR_H_
#define SRC_LIDAR_H_

/*
 * Message headers
 */
#define XGEAR_SYNC0 0xBE
#define XGEAR_SYNC1 0xEF
#define XGEAR_MSG_TYPE_SYSID 1
#define XGEAR_MSG_TYPE_LIDAR 2
#define XGEAR_MSG_TYPE_MOVE_WAYPOINT 3
#define XGEAR_MSG_TYPE_ISAAC_STATUS 4
#define XGEAR_MSG_TYPE_PAYLOAD_STATUS 5
#define XGEAR_BUFFER_SIZE_LIDAR 31
#define XGEAR_SYSID_PAYLOAD_LENGTH 22 // comes from the Xgear Lidar specifications
#define XGEAR_ISAAC_STATUS_PAYLOAD_LENGTH 6
#define XGEAR_PAYLOAD_STATUS_PAYLOAD_LENGTH 12


/*
 * 2 Bytes Sync(0xBEEF) + 1 Byte   Message Type + 2 Bytes Size
 * (plus 2 bytes header checksum)
 */
#define XGEAR_HEADER_LENGTH 7

using namespace std;

/**
 * Lidar data packet
 */
class Lidar {
private:
  float first_;          //value of -1 indicates no reading
  float second_;    //value of -1 indicates no reading
  float third_;         //value of -1 indicates no reading
  float strongest_; //value of -1 indicates no reading
  float last_;          //value of -1 indicates no reading

  uint8_t units_;        //M for meters, F for feet
  uint8_t err_flag_; // error flag
  uint32_t msg_cnt_lidar_; // counter

  uint16_t idx_; // message counter
  uint16_t hdr_chksum_;
  uint16_t dta_chksum_;
  uint16_t datalength_;

  // isaac info
  uint16_t bitfield_;
  uint16_t used_memory_; // % / 0.0015259
  uint16_t used_disk_space_; // % / 0.0015259
  uint32_t msg_cnt_isaac_; // counter

  // payload info
  uint32_t msg_cnt_payload_; // counter
  uint8_t byte1_; // left to payloads discretion
  uint8_t byte2_; // left to payloads discretion
  uint8_t byte3_; // left to payloads discretion
  uint8_t byte4_; // left to payloads discretion
  uint8_t byte5_; // left to payloads discretion
  uint8_t byte6_; // left to payloads discretion

public:
  int packet_size = 31;
  uint8_t buffer[XGEAR_BUFFER_SIZE_LIDAR] = {};

  Lidar(){
    // Lidar values
    first_ = -1;
    second_ = -1;
    third_ = -1;
    strongest_ = -1;
    last_ = -1;
    units_ = 'M';
    err_flag_ = 0;
    msg_cnt_lidar_ = 0;

    // Packet values
    idx_ = 0;
    hdr_chksum_ = 0;
    dta_chksum_ = 0;
    datalength_ = 0;

    // isaac info
    bitfield_ = 0x01; // running
    used_memory_ = (uint16_t)(42/0.0015259); // 42%
    used_disk_space_ = (uint16_t)(69/0.0015259); // 69%
    msg_cnt_isaac_ = 0;

    // payload info
    //bitfield_ = 0x01; // active
    msg_cnt_payload_ = 0;
    byte1_ = 1;
    byte2_ = 2;
    byte3_ = 3;
    byte4_ = 4;
    byte5_ = 5;
    byte6_ = 6;
  }


  /**
   * Destructor - important to close the file
   */
  ~Lidar(){}

   /**
   * Calculate checksum per Xgear documentation
   * @param data
   * @param data_len
   * @return
   */
  static uint16_t calculate_checksum(uint8_t* data, uint16_t data_len)
  {
    uint8_t byte1 = 0;
    uint8_t byte2 = 0;
    for(int x=0; x<data_len; ++x)
    {
      byte1 += data[x];
      byte2 += byte1;
    }
    return (byte1<<8)+byte2;
  }

  /**
   * Fill the lidar buffer to be sent
   */
  void getLidarData(){
    // header
    buffer[0] = XGEAR_SYNC0;
    buffer[1] = XGEAR_SYNC1;
    buffer[2] = XGEAR_MSG_TYPE_LIDAR;

    // header - size
    datalength_ = XGEAR_SYSID_PAYLOAD_LENGTH;
    buffer[3] = (uint8_t)((datalength_ >> 8) & 0xFF); // MSB
    buffer[4] = (uint8_t)(datalength_ & 0xFF); // LSB

    // header - checksum
    hdr_chksum_ = calculate_checksum(buffer+2, (uint16_t)(XGEAR_HEADER_LENGTH-4));
    buffer[5] = (uint8_t)(hdr_chksum_ >> 8);
    buffer[6] = (uint8_t)(hdr_chksum_ & 0xFF);

    // DATA
    // index after the header
    idx_ = XGEAR_HEADER_LENGTH;

    // first
    memcpy(&buffer[idx_], &first_, sizeof(float));
    idx_ += sizeof(float);

    // second
    memcpy(&buffer[idx_], &second_, sizeof(float));
    idx_ += sizeof(float);

    // third
    memcpy(&buffer[idx_], &third_, sizeof(float));
    idx_ += sizeof(float);

    // strongest
    memcpy(&buffer[idx_], &strongest_, sizeof(float));
    idx_ += sizeof(float);

    // last
    memcpy(&buffer[idx_], &last_, sizeof(float));
    idx_ += sizeof(float);

    // units
    buffer[idx_] = units_;
    idx_++;

    // error flag
    buffer[idx_] = err_flag_;
    idx_++;


    // Payload Checksum
    dta_chksum_ = calculate_checksum(&(buffer[XGEAR_HEADER_LENGTH]), (uint16_t)XGEAR_SYSID_PAYLOAD_LENGTH);
    buffer[idx_] = (uint8_t)(dta_chksum_ >> 8);
    idx_++;
    buffer[idx_] = (uint8_t)(dta_chksum_ & 0xFF);
    idx_++;

    msg_cnt_lidar_++;

    //cout << "Lidar packet #" << msg_cnt_lidar_ << endl;
  }


  /**
   * Prepare fake Isaac status packet
   */
  void getIsaacData(){
    // header
    buffer[0] = XGEAR_SYNC0;
    buffer[1] = XGEAR_SYNC1;
    buffer[2] = XGEAR_MSG_TYPE_ISAAC_STATUS;

    // header - size
    datalength_ = XGEAR_ISAAC_STATUS_PAYLOAD_LENGTH;
    buffer[3] = (uint8_t)((datalength_ >> 8) & 0xFF); // MSB
    buffer[4] = (uint8_t)(datalength_ & 0xFF); // LSB

    // header - checksum
    hdr_chksum_ = calculate_checksum(buffer+2, (uint16_t)(XGEAR_HEADER_LENGTH-4));
    buffer[5] = (uint8_t)(hdr_chksum_ >> 8);
    buffer[6] = (uint8_t)(hdr_chksum_ & 0xFF);

    // DATA
    // index after the header
    idx_ = XGEAR_HEADER_LENGTH;

    // bitfield
    memcpy(&buffer[idx_], &bitfield_, sizeof(uint16_t));
    idx_ += sizeof(uint16_t);

    // used_memory
    memcpy(&buffer[idx_], &used_memory_, sizeof(uint16_t));
    idx_ += sizeof(uint16_t);

    // used disk_space
    memcpy(&buffer[idx_], &used_disk_space_, sizeof(uint16_t));
    idx_ += sizeof(uint16_t);

    // Payload Checksum
    dta_chksum_ = calculate_checksum(&(buffer[XGEAR_HEADER_LENGTH]), (uint16_t)XGEAR_ISAAC_STATUS_PAYLOAD_LENGTH);
    buffer[idx_] = (uint8_t)(dta_chksum_ >> 8);
    idx_++;
    buffer[idx_] = (uint8_t)(dta_chksum_ & 0xFF);
    idx_++;

    msg_cnt_isaac_++;

    //cout << "Isaac packet #" << msg_cnt_isaac_ << endl;
  }



  /**
   * Prepare fake paylaod status packet
   */
  void getPayloadData(){
    // header
    buffer[0] = XGEAR_SYNC0;
    buffer[1] = XGEAR_SYNC1;
    buffer[2] = XGEAR_MSG_TYPE_PAYLOAD_STATUS;

    // header - size
    datalength_ = XGEAR_PAYLOAD_STATUS_PAYLOAD_LENGTH;
    buffer[3] = (uint8_t)((datalength_ >> 8) & 0xFF); // MSB
    buffer[4] = (uint8_t)(datalength_ & 0xFF); // LSB

    // header - checksum
    hdr_chksum_ = calculate_checksum(buffer+2, (uint16_t)(XGEAR_HEADER_LENGTH-4));
    buffer[5] = (uint8_t)(hdr_chksum_ >> 8);
    buffer[6] = (uint8_t)(hdr_chksum_ & 0xFF);

    // DATA
    // index after the header
    idx_ = XGEAR_HEADER_LENGTH;

    // bitfield
    memcpy(&buffer[idx_], &bitfield_, sizeof(uint16_t));
    idx_ += sizeof(uint16_t);

    // used_memory
    memcpy(&buffer[idx_], &used_memory_, sizeof(uint16_t));
    idx_ += sizeof(uint16_t);

    // used disk_space
    memcpy(&buffer[idx_], &used_disk_space_, sizeof(uint16_t));
    idx_ += sizeof(uint16_t);

    // additional bytes
    buffer[idx_] = byte1_;
    idx_++;
    buffer[idx_] = byte2_;
    idx_++;
    buffer[idx_] = byte3_;
    idx_++;
    buffer[idx_] = byte4_;
    idx_++;
    buffer[idx_] = byte5_;
    idx_++;
    buffer[idx_] = byte6_;
    idx_++;

    // Payload Checksum
    dta_chksum_ = calculate_checksum(&(buffer[XGEAR_HEADER_LENGTH]), (uint16_t)XGEAR_PAYLOAD_STATUS_PAYLOAD_LENGTH);
    buffer[idx_] = (uint8_t)(dta_chksum_ >> 8);
    idx_++;
    buffer[idx_] = (uint8_t)(dta_chksum_ & 0xFF);
    idx_++;

    msg_cnt_payload_++;

    //cout << "Payload packet #" << msg_cnt_payload_ << endl;
  }

  /**
   * Get number of bytes to send
   * @return idx
   */
  uint16_t getIdx(){
    return idx_;
  }

};



#endif /* SRC_LIDAR_H_ */
