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

#if PERIODIC_TELEMETRY
#include "subsystems/datalink/telemetry.h"
#endif

// for xgear rx messages
#include "modules/loggers/xgear_lidar.h"
#include "modules/loggers/xgear_status.h"

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
#define XGEAR_SYSID_PAYLOAD_LENGTH 165 // comes from the Xgear SysIDA specifications
//note: should be at some point taken from XGEAR conf file

// max length of rx data
#define XGEAR_RX_DATA_LENGTH 31

// number of rx buffers to switch between
#define XGEAR_NUM_RX_BUFFERS 2

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
#define XGEAR_CHK_LEN 2

#ifndef USE_CHIBIOS_RTOS
#error "Xgear module is for RT Paparazzi only!"
#endif

#include "ch.h"
#include "hal.h"


/*
 * Mutex guard
 */
extern mutex_t mtx_xgear;
#define CH_THREAD_AREA_XGEAR_RX 1024
void thd_xgear_rx(void *arg);

/*
 * Message status for parsing
 */
enum MsgStatus {
  MsgSync0,
  MsgSync1,
  MsgType,
  MsgSize,
  MsgHdrChksum,
  MsgData,
  MsgDataChksum
};

struct Xgear {
  uint8_t msg_buf[XGEAR_BUFFER_SIZE];
  uint8_t rx_buf[XGEAR_NUM_RX_BUFFERS][XGEAR_RX_DATA_LENGTH];
  //volatile uint8_t rx_buf_full[XGEAR_NUM_RX_BUFFERS];
  uint8_t* prev_rx_buf;
  uint8_t* cur_rx_buf;
  volatile uint8_t rx_buf_cnt;
  uint16_t rxchar_cnt;


  uint32_t msg_cnt;
  uint16_t good_msg;
  uint16_t idx;

  enum MsgStatus status;
  bool_t msg_available;
  uint8_t type;
  uint16_t datalength;

  uint32_t chksm_error;
  uint32_t hdr_error;
  uint16_t rx_chksum;
  uint16_t calc_chksum;

  uint16_t overrun_error;
  uint16_t noise_error;
  uint16_t framing_error;
};

extern struct Xgear xgear_tx;
extern struct Xgear xgear_rx;

void xgear_init(void);
void xgear_periodic(void);
void xgear_parse(uint8_t c);
void xgear_read_message(void);

uint16_t calculate_checksum(uint8_t* data, uint16_t data_len);

void set_status(uint16_t* stat);

#endif /* XGEAR_MODULE_H_ */
