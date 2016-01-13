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
 * @file xgear_status.h
 *
 * Xgear status submodule. Covers status of Payload and Isaac
 *
 * @author Michal Podhradsky <michal.podhradsky@aggiemail.usu.edu>
 */
#ifndef SW_AIRBORNE_MODULES_LOGGERS_XGEAR_STATUS_H_
#define SW_AIRBORNE_MODULES_LOGGERS_XGEAR_STATUS_H_

#include "modules/loggers/xgear.h"

#define ISAAC_BLACK_BOX_RUNNING 0x01

/*
 * ISAAC Status info
 */
struct IsaacStatus {
  uint16_t bitfield; // encoded status field
  uint16_t used_mem; // percent used memory
  uint16_t used_disk; // percent used disk space

  uint8_t black_box; // Black_Box_Behavior

  uint32_t msg_cnt; // counter
};

extern struct IsaacStatus isaac_status;


#define PAYLOAD_ACTIVE 0x01

/*
 * Paylaod Status info
 */
struct PayloadStatus {
  uint16_t bitfield; // encoded status field
  uint16_t used_mem; // percent used memory
  uint16_t used_disk; // percent used disk space
  uint8_t byte1; // left to payloads discretion
  uint8_t byte2; // left to payloads discretion
  uint8_t byte3; // left to payloads discretion
  uint8_t byte4; // left to payloads discretion
  uint8_t byte5; // left to payloads discretion
  uint8_t byte6; // left to payloads discretion

  uint8_t active; // payload active

  uint32_t msg_cnt; // counter
};

extern struct PayloadStatus payload_status;


void xgear_status_init(void);
void xgear_read_isaac_status(uint8_t buf[]);
void xgear_update_isaac_status(void);

void xgear_read_payload_status(uint8_t buf[]);
void xgear_update_payload_status(void);

#endif /* SW_AIRBORNE_MODULES_LOGGERS_XGEAR_STATUS_H_ */
