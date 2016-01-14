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
 * @file xgear_lidar.h
 *
 * Xgear industrial module. This module is only for storing
 *  data that were recived from Xgear Lidar message. The data are periodically
 *  send over telemetry.
 *
 * @author Michal Podhradsky <michal.podhradsky@aggiemail.usu.edu>
 */
#ifndef XGEAR_LIDAR_H
#define XGEAR_LIDAR_H

#include "modules/loggers/xgear.h"

struct XgearLidar {
  float first;          //value of -1 indicates no reading
  float second;    //value of -1 indicates no reading
  float third;         //value of -1 indicates no reading
  float strongest; //value of -1 indicates no reading
  float last;          //value of -1 indicates no reading

  uint8_t units;        //M for meters, F for feet
  uint8_t err_flag; // error flag
  uint32_t msg_cnt; // counter
};

extern struct XgearLidar lidar;

void xgear_lidar_init(void);
void xgear_read_lidar(uint8_t buf[]);
void xgear_lidar_update_units(void);

#endif /* XGEAR_LIDAR_H */
