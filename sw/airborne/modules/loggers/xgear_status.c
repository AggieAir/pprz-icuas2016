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
 * @file xgear_status.c
 *
 * Xgear status submodule. Covers status of Payload and Isaac
 *
 * @author Michal Podhradsky <michal.podhradsky@aggiemail.usu.edu>
 */
#include "modules/loggers/xgear_status.h"

struct IsaacStatus isaac_status;
struct PayloadStatus payload_status;

#if PERIODIC_TELEMETRY

static void send_isaac_status(struct transport_tx *trans, struct link_device *dev){
  pprz_msg_send_ISAAC_STATUS(trans, dev, AC_ID,
      &isaac_status.black_box,
      &isaac_status.used_mem,
      &isaac_status.used_disk,
      &isaac_status.msg_cnt);
}

static void send_payload_status(struct transport_tx *trans, struct link_device *dev){
  pprz_msg_send_PAYLOAD_STATUS(trans, dev, AC_ID,
      &payload_status.active,
      &payload_status.used_mem,
      &payload_status.used_disk,
      &payload_status.msg_cnt,
      &payload_status.byte1,
      &payload_status.byte2,
      &payload_status.byte3,
      &payload_status.byte4,
      &payload_status.byte5,
      &payload_status.byte6);
}
#endif

/**
 * Init function
 */
void xgear_status_init(void) {
  isaac_status.bitfield = 0;
  isaac_status.used_disk = 0;
  isaac_status.used_mem = 0;
  isaac_status.msg_cnt = 0;
  isaac_status.black_box = 0;

  payload_status.bitfield = 0;
  payload_status.used_disk = 0;
  payload_status.used_mem = 0;
  payload_status.msg_cnt = 0;
  payload_status.active = 0;
  payload_status.byte1 = 0;
  payload_status.byte2 = 0;
  payload_status.byte3 = 0;
  payload_status.byte4 = 0;
  payload_status.byte5 = 0;
  payload_status.byte6 = 0;


#if PERIODIC_TELEMETRY
  register_periodic_telemetry(DefaultPeriodic, PPRZ_MSG_ID_ISAAC_STATUS, send_isaac_status);
  register_periodic_telemetry(DefaultPeriodic, PPRZ_MSG_ID_PAYLOAD_STATUS, send_payload_status);
#endif
}


/**
 * Read ISAAC data
  * @param buffer with payload data
 */
void xgear_read_isaac_status(uint8_t buf[]){
  static uint16_t idx;

  idx = 0;

  // status bitfield
  memcpy(&isaac_status.bitfield, &buf[idx], sizeof(uint16_t));
  idx += sizeof(uint16_t);

  // used memory
  memcpy(&isaac_status.used_mem, &buf[idx], sizeof(uint16_t));
  idx += sizeof(uint16_t);

  // used disk space
  memcpy(&isaac_status.used_disk, &buf[idx], sizeof(uint16_t));
  idx += sizeof(uint16_t);

  xgear_update_isaac_status();

  // update message counter
  isaac_status.msg_cnt++;
}


/**
 * Update status from the bitfield
 */
void xgear_update_isaac_status(void) {
  // Black box
  isaac_status.black_box = (isaac_status.bitfield & ISAAC_BLACK_BOX_RUNNING);
}


/**
 * Read Payload data
  * @param buffer with payload data
 */
void xgear_read_payload_status(uint8_t buf[]){
  static uint16_t idx;

  idx = 0;

  // status bitfield
  memcpy(&payload_status.bitfield, &buf[idx], sizeof(uint16_t));
  idx += sizeof(uint16_t);

  // used memory
  memcpy(&payload_status.used_mem, &buf[idx], sizeof(uint16_t));
  idx += sizeof(uint16_t);

  // used disk space
  memcpy(&payload_status.used_disk, &buf[idx], sizeof(uint16_t));
  idx += sizeof(uint16_t);

  // additional bytes
  payload_status.byte1 = buf[idx];
  idx++;

  payload_status.byte2 = buf[idx];
  idx++;

  payload_status.byte3 = buf[idx];
  idx++;

  payload_status.byte4 = buf[idx];
  idx++;

  payload_status.byte5 = buf[idx];
  idx++;

  payload_status.byte6 = buf[idx];
  idx++;

  xgear_update_payload_status();

  // update message counter
  payload_status.msg_cnt++;
}

/**
 * Update status from the bitfield
 */
void xgear_update_payload_status(void) {
  // Active?
  payload_status.active = (payload_status.bitfield & PAYLOAD_ACTIVE);
}
