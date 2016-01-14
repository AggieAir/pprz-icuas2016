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
 * @file xgear_lidar.c
 *
 * Xgear industrial module. This module is only for storing
 *  data that were recived from Xgear Lidar message. The data are periodically
 *  send over telemetry.
 *
 * @author Michal Podhradsky <michal.podhradsky@aggiemail.usu.edu>
 */
#include "modules/loggers/xgear_lidar.h"

struct XgearLidar lidar;

#if PERIODIC_TELEMETRY
static void send_lidar(struct transport_tx *trans, struct link_device *dev){
  pprz_msg_send_LIDAR(trans, dev, AC_ID,
      &lidar.first,
      &lidar.second,
      &lidar.third,
      &lidar.strongest,
      &lidar.last,
      &lidar.err_flag,
      &lidar.msg_cnt);
}
#endif


/**
 * Init function
 */
void xgear_lidar_init(void) {
  lidar.first = 0;
  lidar.second = 0;
  lidar.third = 0;
  lidar.strongest = 0;
  lidar.last = 0;
  lidar.units = 0;
  lidar.err_flag = 0;
  lidar.msg_cnt = 0;

#if PERIODIC_TELEMETRY
  register_periodic_telemetry(DefaultPeriodic, PPRZ_MSG_ID_LIDAR, send_lidar);
#endif
}

/**
 * Read LIDAR data
 * @param buffer with payload data
 */
void xgear_read_lidar(uint8_t buf[]){
  static uint16_t idx;

  idx = 0;

  // first measurement
  memcpy(&lidar.first, &buf[idx], sizeof(float));
  idx += sizeof(float);

  // second measurement
  memcpy(&lidar.second, &buf[idx], sizeof(float));
  idx += sizeof(float);

  // third measurement
  memcpy(&lidar.third, &buf[idx], sizeof(float));
  idx += sizeof(float);

  // strongest measurement
  memcpy(&lidar.strongest, &buf[idx], sizeof(float));
  idx += sizeof(float);

  // last measurement
  memcpy(&lidar.last, &buf[idx], sizeof(float));
  idx += sizeof(float);

  // units
  lidar.units = buf[idx];
  idx++;

  // error flag
  lidar.err_flag = buf[idx];
  idx++;

  xgear_lidar_update_units();

  // update message counter
  lidar.msg_cnt++;
}


/**
 * Update units to meters
 * (in case they are not already in meters)
 */
void xgear_lidar_update_units(void) {
  if (lidar.units == 'F') {
    // units are in feet
    lidar.first = MetersOfFeet(lidar.first);
    lidar.second = MetersOfFeet(lidar.second);
    lidar.third = MetersOfFeet(lidar.third);
    lidar.strongest = MetersOfFeet(lidar.strongest);
    lidar.last = MetersOfFeet(lidar.last);
  }
}
