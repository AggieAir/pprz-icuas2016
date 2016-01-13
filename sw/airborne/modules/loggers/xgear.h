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
 * @file xgear.h
 *
 * Hardware In The Loop AP end
 * Also knows as XGear, for more look atL:
 * https://docs.google.com/document/d/1vueyAJrlhr70csdVlQ7Yu1xyIsiRP2uI2NHQ8X3EaRo/edit?usp=sharing
 *
 * @author Michal Podhradsky <michal.podhradsky@aggiemail.usu.edu>
 */
#ifndef XGEAR_MODULE_H
#define XGEAR_MODULE_H


#include "std.h"
#include "subsystems/commands.h"

// for ap_status
#include "autopilot.h"
#include "subsystems/radio_control.h"

#include "mcu_periph/uart.h"
#include "mcu_periph/usb_serial.h"
#include "subsystems/ins/ins_vectornav.h"
#include "subsystems/imu.h"
#include "subsystems/gps.h"


/*
 * Message headers
 */
#define XGEAR_SYNC0 0xBE
#define XGEAR_SYNC1 0xEF
#define XGEAR_MSG_TYPE 1 // == SysIDA
#define XGEAR_PAYLOAD_LENGTH 165 // comes from the Xgear SysIDA specifications
//note: should be at some point taken from XGEAR conf file

/*
 * 2 Bytes Sync(0xBEEF) + 1 Byte   Message Type + 2 Bytes Size
 * (plus 2 bytes header checksum)
 */
#define XGEAR_HEADER_LENGTH 7

/*
 * Pointers in the buffer
 */
#define XGEAR_HEADER_SIZE 3
#define XGEAR_HEADER_CHKSUM 5

#define XGEAR_BUFFER_SIZE 512

#define XGEAR_AP_MODE_BITSHIFT 4
#define XGEAR_LAUNCH_BITSHIFT 12


struct Xgear {
  uint8_t msg_buf[XGEAR_BUFFER_SIZE];
  uint32_t msg_cnt;
  uint16_t chk_err;
  uint16_t good_msg;
};

extern struct Xgear xgear;

void xgear_init(void);

void xgear_periodic(void);

uint16_t calculate_checksum(uint8_t* data, uint16_t data_len);

void set_status(uint16_t* stat);

#endif /* XGEAR_MODULE_H_ */
