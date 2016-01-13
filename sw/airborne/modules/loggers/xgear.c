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
 * @file xgear.c
 *
 * Hardware In The Loop AP end
 * Also knows as XGear, for more look at:
 * https://docs.google.com/document/d/1vueyAJrlhr70csdVlQ7Yu1xyIsiRP2uI2NHQ8X3EaRo/edit?usp=sharing
 *
 * @author Michal Podhradsky <michal.podhradsky@aggiemail.usu.edu>
 */
#include "modules/loggers/xgear.h"

struct Xgear xgear;

void xgear_init(void)
{
  xgear.msg_cnt = 0;
  xgear.chk_err = 0;
  xgear.good_msg = 0;
  memset(xgear.msg_buf, 0, sizeof(xgear.msg_buf));
}

/**
 * Packet Structure:
2 Bytes Sync(0xBEEF)
1 Byte   Message Type
2 Bytes Size
2 Bytes Header Checksum(Type and Size)
X Bytes Data
2 Bytes Data Checksum
 */
void xgear_periodic(void)
{
  static uint16_t hdr_chksum, dta_chksum, idx;

  // header
  xgear.msg_buf[0] = XGEAR_SYNC0;
  xgear.msg_buf[1] = XGEAR_SYNC1;
  xgear.msg_buf[2] = XGEAR_MSG_TYPE;

  // header - size
  static uint16_t datalength = XGEAR_PAYLOAD_LENGTH;
  xgear.msg_buf[3] = (uint8_t)((datalength >> 8) & 0xFF); // MSB
  xgear.msg_buf[4] = (uint8_t)(datalength & 0xFF); // LSB

  // header - checksum
  hdr_chksum = calculate_checksum(xgear.msg_buf+2, (uint16_t)(XGEAR_HEADER_LENGTH-4));
  xgear.msg_buf[5] = (uint8_t)(hdr_chksum >> 8);
  xgear.msg_buf[6] = (uint8_t)(hdr_chksum & 0xFF);
  // END OF HEADER

  // DATA
  // index after the header
  idx = XGEAR_HEADER_LENGTH;

  // timestamp
  memcpy(&xgear.msg_buf[idx], &ins_vn.timestamp, sizeof(float));
  idx += sizeof(float);

  // YawPitchRoll [deg]
  memcpy(&xgear.msg_buf[idx], &ins_vn.ypr, 3*sizeof(float));
  idx += 3*sizeof(float);

  // AngularRate
  memcpy(&xgear.msg_buf[idx], &imuf.gyro, 3*sizeof(float));
  idx += 3*sizeof(float);

  // Position LLA
  memcpy(&xgear.msg_buf[idx], &ins_vn.pos_lla, 3*sizeof(double));
  idx += 3*sizeof(double);

  // Velocity NED
  memcpy(&xgear.msg_buf[idx], &ins_vn.vel_ned, 3*sizeof(float));
  idx += 3*sizeof(float);

  // Accel
  memcpy(&xgear.msg_buf[idx], &imuf.accel, 3*sizeof(float));
  idx += 3*sizeof(float);

  // Tow
  memcpy(&xgear.msg_buf[idx], &gps.tow, sizeof(uint32_t));
  idx += sizeof(uint32_t);

  //num sats, uint8
  xgear.msg_buf[idx] = gps.num_sv;
  idx++;

  //gps fix, uint8
  xgear.msg_buf[idx] = gps.fix;
  idx++;

  //posU, float[3]
  memcpy(&xgear.msg_buf[idx], &ins_vn.posU, 3*sizeof(float));
  idx += 3*sizeof(float);

  //velU, float
  memcpy(&xgear.msg_buf[idx], &ins_vn.velU, sizeof(float));
  idx += sizeof(float);

  //linear acceleration imu-body frame, float [m/s^2]
  // Body acceleration without gravity
  memcpy(&xgear.msg_buf[idx], &ins_vn.lin_accel, 3*sizeof(float));
  idx += 3*sizeof(float);

  //YprU, float[3]
  memcpy(&xgear.msg_buf[idx], &ins_vn.YprU, 3*sizeof(float));
  idx += 3*sizeof(float);

  //instatus, uint16
  memcpy(&xgear.msg_buf[idx], &ins_vn.ins_status, 3*sizeof(uint16_t));
  idx += sizeof(uint16_t);

  //Vel body, float [m/s]
  // The estimated velocity in the body (i.e. imu) frame, given in m/s.
  memcpy(&xgear.msg_buf[idx], &ins_vn.vel_body, 3*sizeof(float));
  idx += 3*sizeof(float);

  // ap_time, float, [s]
  static float ap_time;
  ap_time = get_sys_time_float();
  memcpy(&xgear.msg_buf[idx], &ap_time, sizeof(float));
  idx += sizeof(float);

  // NUmber of commands
  xgear.msg_buf[idx] = (uint8_t)COMMANDS_NB;
  idx++;

#if XGEAR_VTOL // VTOL CONFIGURATION
  // Servo #0
  memcpy(&xgear.msg_buf[idx], &commands[0], sizeof(pprz_t));
  idx += sizeof(pprz_t);

  // Servo #1
  memcpy(&xgear.msg_buf[idx], &commands[1], sizeof(pprz_t));
  idx += sizeof(pprz_t);

  // Servo #2
  memcpy(&xgear.msg_buf[idx], &commands[2], sizeof(pprz_t));
  idx += sizeof(pprz_t);

  // Servo #3
  memcpy(&xgear.msg_buf[idx], &commands[3], sizeof(pprz_t));
  idx += sizeof(pprz_t);

  // Servo #4 (Hexarotor only)
if (COMMANDS_NB > 4) {
  memcpy(&xgear.msg_buf[idx], &commands[4], sizeof(pprz_t));
}
else {
  static pprz_t dummy_cmd = 0;
    memcpy(&xgear.msg_buf[idx], &dummy_cmd, sizeof(pprz_t));
}
  idx += sizeof(pprz_t);
#else // FIXEDWING CONFIGURATION
  // Command THROTTLE
  memcpy(&xgear.msg_buf[idx], &commands[COMMAND_THROTTLE], sizeof(pprz_t));
  idx += sizeof(pprz_t);

  // command ROLL
  memcpy(&xgear.msg_buf[idx], &commands[COMMAND_ROLL], sizeof(pprz_t));
  idx += sizeof(pprz_t);

  // command PITCH
  memcpy(&xgear.msg_buf[idx], &commands[COMMAND_PITCH], sizeof(pprz_t));
  idx += sizeof(pprz_t);

  // command YAW
  memcpy(&xgear.msg_buf[idx], &commands[COMMAND_YAW], sizeof(pprz_t));
  idx += sizeof(pprz_t);

  // command FLAPS
#ifdef COMMAND_FLAPS
  memcpy(&xgear.msg_buf[idx], &commands[COMMAND_FLAPS], sizeof(pprz_t));
#else
  static pprz_t dummy_cmd = 0;
  memcpy(&xgear.msg_buf[idx], &dummy_cmd, sizeof(pprz_t));
#endif
  idx += sizeof(pprz_t);
#endif /* XGEAR VTOL */

  // alpha, float
  // NOTE: zero for now
  static float dummy_alpha = 0;
  memcpy(&xgear.msg_buf[idx], &dummy_alpha, sizeof(float));
  idx += sizeof(float);

  // beta, float
  // NOTE: zero for now
  static float dummy_beta = 0;
  memcpy(&xgear.msg_buf[idx], &dummy_beta, sizeof(float));
  idx += sizeof(float);

  // airspeed, float
  // NOTE: zero for now
  static float dummy_airspeed = 0;
  memcpy(&xgear.msg_buf[idx], &dummy_airspeed, sizeof(float));
  idx += sizeof(float);

  // ap_settings, uint16_t
  static uint16_t status = 0;
  set_status(&status);
  memcpy(&xgear.msg_buf[idx], &status, sizeof(uint16_t));
  idx += sizeof(uint16_t);
  // END DATA


  // Payload Checksum
  dta_chksum = calculate_checksum(&(xgear.msg_buf[XGEAR_HEADER_LENGTH]), (uint16_t)XGEAR_PAYLOAD_LENGTH);
  xgear.msg_buf[idx] = (uint8_t)(dta_chksum >> 8);
  idx++;
  xgear.msg_buf[idx] = (uint8_t)(dta_chksum & 0xFF);
  idx++;

  // Send
  for (int i=0; i<idx; i++) {
    uart_put_byte(&XGEAR_PORT, xgear.msg_buf[i]);
  }

  xgear.msg_cnt++;
}


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
  for(int x=0; x<data_len; ++x)
  {
    byte1 += data[x];
    byte2 += byte1;
  }
  return (byte1<<8)+byte2;
}

/**
 * Set AP status for Xgear
 * See https://docs.google.com/spreadsheets/d/1hEYYMueguAe5Uva-TMq7Jdmbc7zPLHwkmKGFTzhKvXE/edit?usp=sharing
 * for details
 * @param status - where the status should be saved
 */
void set_status(uint16_t* status) {
  uint16_t tmp = 0;
  // TODO: SIM_STATUS

  // TODO: Datalink status

  // Radio status
#if defined RADIO_CONTROL
  tmp = (tmp | (radio_control.status << 2));
#endif


#if XGEAR_VTOL // VTOL CONFIGURATION
INFO("XGEAR in VTOL configuration")
  // AP mode
  tmp = (tmp | ((uint8_t)autopilot_mode << XGEAR_AP_MODE_BITSHIFT));

  // Auto2 mode
  tmp = (tmp | ((uint8_t)autopilot_mode_auto2 << (XGEAR_AP_MODE_BITSHIFT*2)));

  // In flight
  tmp = (tmp | (uint8_t)autopilot_in_flight << XGEAR_LAUNCH_BITSHIFT);

#else // FIXEDWING CONFIGURATION
  INFO("XGEAR in FIXEDWING configuration")
  // AP mode
  tmp = (tmp | ((uint8_t)pprz_mode << XGEAR_AP_MODE_BITSHIFT));

  // Lateral mode
  tmp = (tmp | ((uint8_t)lateral_mode << (XGEAR_AP_MODE_BITSHIFT*2)));

  // Launch
  tmp = (tmp | (uint8_t)launch << XGEAR_LAUNCH_BITSHIFT);
#endif /* XGEAR VTOL */

  *status = tmp;
}
