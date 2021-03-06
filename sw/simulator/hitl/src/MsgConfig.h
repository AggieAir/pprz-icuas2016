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
 * @file MsgConfig.h
 *
 * HITL demo version - general message configuration
 *
 * @author Michal Podhradsky <michal.podhradsky@aggiemail.usu.edu>
 */
#ifndef MSGCONFIG_H_
#define MSGCONFIG_H_

#include "generated/airframe.h"
#include "generated/flight_plan.h"
#include "paparazzi.h"

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

/*
 * Message headers
 */
#define HITL_SYNC 0xFA
#define BUF_SIZE 174 // todo maybe smaller buffer
#define HITL_DATALENGTH 167//(ACTUATORS_NB*2+4) // for quadrotor
#define CHK_LEN 2


/*
 * Message headers
 */
#define HITL_SYNC0 0xBE
#define HITL_SYNC1 0xEF
#define HITL_MSG_TYPE 1 // == SysIDA
#define HITL_PAYLOAD_LENGTH 165 // comes from the Xgear SysIDA specifications
//note: should be at some point taken from XGEAR conf file

/*
 * 2 Bytes Sync(0xBEEF) + 1 Byte   Message Type + 2 Bytes Size
 * (plus 2 bytes header checksum)
 */
#define HITL_HEADER_LENGTH 7

/*
 * Port settings
 */
#define AUTOPILOT_UPDATE_RATE 16//2 //in ms

#define AP_BAUD 3000000
#define AP_DEV "/dev/ttyUSB2"

#define VECTORNAV_UPDATE_RATE 2 //in ms
#define VN_BAUD 921600
#define VN_DEV "/dev/ttyUSB1"

/*
 * Default actuators number (8 is the max available on Lia)
 */
#ifndef ACTUATORS_NB
#define ACTUATORS_NB 8
#endif


//#define MAX_PPRZ 9600



#endif /* MSGCONFIG_H_ */
