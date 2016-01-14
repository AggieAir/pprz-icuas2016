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

struct Xgear xgear_tx;
struct Xgear xgear_rx;

static event_source_t eventXgearRx;
#define EVT_XGEAR_RX 8
volatile uint8_t xgear_flag_tx;

/*
 * Mutex guard
 */
mutex_t mtx_xgear;

#if PERIODIC_TELEMETRY
static void send_xgear_info(struct transport_tx *trans, struct link_device *dev){
  // rx counters
  static uint16_t rx_last_cnt = 0;
  static uint16_t rx_sec_cnt = 0;
  rx_sec_cnt = xgear_rx.msg_cnt -  rx_last_cnt;

  // tx counter
  static uint16_t tx_last_cnt = 0;
  static uint16_t tx_sec_cnt = 0;
  tx_sec_cnt = xgear_tx.msg_cnt -  tx_last_cnt;

    // guard with mutex
    chMtxLock(&mtx_xgear);

    pprz_msg_send_XGEAR_INFO(trans, dev, AC_ID,
              &xgear_tx.msg_cnt,
              &tx_sec_cnt,
              &xgear_rx.msg_cnt,
              &rx_sec_cnt,
              &xgear_rx.chksm_error,
              &xgear_rx.hdr_error,
              &xgear_rx.status,
              &xgear_rx.type,
              &xgear_rx.datalength,
              &xgear_rx.calc_chksum,
              &xgear_rx.rx_chksum,
              &xgear_rx.rxchar_cnt,
              &xgear_rx.overrun_error,
              &xgear_rx.noise_error,
              &xgear_rx.framing_error);

    // Mutex guard
    chMtxUnlock(&mtx_xgear);

      // update counters
        rx_last_cnt = xgear_rx.msg_cnt;
        tx_last_cnt = xgear_tx.msg_cnt;
}
#endif  /* PERIODIC_TELEMETRY */


/**
 * This callback is invoked when a transmission has physically completed.
 */
static void xgear_txend(UARTDriver *uartp) {
  chSysLockFromISR();
  xgear_flag_tx = 0;
  chSysUnlockFromISR();
  (void) uartp;
}

/**
 * This callback is invoked when a receive buffer has been completely written.
 *
 * Broadcast an RX event, then swap the rx buffers and start receiving again
 */
static void xgear_rxend(UARTDriver *uartp) {
  (void) uartp;

  // increment buffer counter
  xgear_rx.prev_rx_buf = xgear_rx.cur_rx_buf;
  xgear_rx.rx_buf_cnt++;
  xgear_rx.rx_buf_cnt = xgear_rx.rx_buf_cnt % XGEAR_NUM_RX_BUFFERS;
  xgear_rx.cur_rx_buf = xgear_rx.rx_buf[xgear_rx.rx_buf_cnt];

  // broadcast an event
  chSysLockFromISR();
  chEvtBroadcastFlagsI(&eventXgearRx, EVT_XGEAR_RX);

  // start receiving more data
  uartStartReceiveI(&XGEAR_PORT, (size_t)XGEAR_RX_DATA_LENGTH, xgear_rx.cur_rx_buf);
  chSysUnlockFromISR();


}

/**
 * This callback is invoked when a character is received but the application
 * was not ready to receive it, the character is passed as parameter.
 *
 * This will typically happen between rxend callback and processing the buffer
 */
static void xgear_rxchar(UARTDriver *uartp, uint16_t c) {
  (void)uartp;
  (void)c;
  xgear_rx.rxchar_cnt++;
  /*
  xgear_parse((uint8_t)c);
  if (xgear_rx.msg_available == TRUE) {
    chSysLockFromISR();
    chEvtBroadcastFlagsI(&eventXgearRx, EVT_XGEAR_RX);
    chSysUnlockFromISR();
    xgear_rx.msg_available  = FALSE;
  }
  */
}

/**
 * This callback is invoked on a receive error, the errors mask is passed
 * as parameter.
 *
 * Since we already detect errors on the line with hdr/checksum errors, this
 * is not really needed.
 */
static void xgear_rxerr(UARTDriver *uartp, uartflags_t e) {
  if (e & UART_OVERRUN_ERROR) {
    xgear_rx.overrun_error++;
  }
  if (e & UART_NOISE_ERROR ) {
    xgear_rx.noise_error++;
  }
  if (e & UART_FRAMING_ERROR ) {
    xgear_rx.framing_error++;
  }
  (void)uartp;
}


/**
 * UART driver configuration structure.
 */
static UARTConfig uart_cfg_xgear = {
    NULL,                                                     /* end of tx_buf   */
    xgear_txend,                                              /* physical end tx */
    xgear_rxend,                                              /* rx buf filled */
    xgear_rxchar,                                             /* char received of RX_IDLE */
    xgear_rxerr,                                              /* rx error       */
    XGEAR_BAUD,                                               /*     BITRATE    */
    0,                                                        /*    USART CR1   */
    USART_CR2_STOP1_BITS,                                     /*    USART CR2   */
    0                                                         /*    USART CR3   */
};

/**
 * Xgear RX thread
 */
static THD_WORKING_AREA(wa_thd_xgear_rx, CH_THREAD_AREA_XGEAR_RX);
void thd_xgear_rx(void *arg)
{
  chRegSetThreadName("module_xgear_rx");
  (void) arg;

  // UART settings
  uartStart(&XGEAR_PORT, &uart_cfg_xgear);
  uartStopSend(&XGEAR_PORT);
  uartStopReceive(&XGEAR_PORT);


  event_listener_t elXgearRx;
  chEvtRegister(&eventXgearRx, &elXgearRx, EVT_XGEAR_RX);

  // start receiving
  uartStartReceive(&XGEAR_PORT, (size_t)XGEAR_RX_DATA_LENGTH, xgear_rx.cur_rx_buf);

  while (TRUE)
  {
    chEvtWaitAny(EVENT_MASK(EVT_XGEAR_RX));
    chEvtGetAndClearFlags(&elXgearRx);

    // we got a full buffer
    for (int i = 0;i<XGEAR_RX_DATA_LENGTH;i++){
      xgear_parse((uint8_t)xgear_rx.prev_rx_buf[i]);
      if (xgear_rx.msg_available) {

        // guard with mutex
        chMtxLock(&mtx_xgear);

        xgear_read_message();

        // Mutex guard
        chMtxUnlock(&mtx_xgear);
        xgear_rx.msg_available  = FALSE;
      }
    }
  }
}



void xgear_init(void)
{
  // Transmit
  xgear_tx.msg_cnt = 0;
  xgear_tx.chksm_error = 0;
  xgear_tx.hdr_error = 0;
  xgear_tx.rx_chksum = 0;
  xgear_tx.calc_chksum = 0;
  xgear_tx.good_msg = 0;
  xgear_tx.idx = 0;
  memset(xgear_tx.msg_buf, 0, sizeof(xgear_tx.msg_buf));

  // Receive
  xgear_rx.msg_cnt = 0;
  xgear_rx.chksm_error = 0;
  xgear_rx.hdr_error = 0;
  xgear_rx.rx_chksum = 0;
  xgear_rx.calc_chksum = 0;
  xgear_rx.good_msg = 0;
  xgear_rx.idx = 0;
  memset(xgear_rx.msg_buf, 0, sizeof(xgear_rx.msg_buf));
  // fill rx buffers
  for (int i=0;i<XGEAR_NUM_RX_BUFFERS;i++){
    memset(xgear_rx.rx_buf[i], 0, sizeof(xgear_rx.rx_buf[i]));
  }
  // initialize buffer pointer to the first buffer
  xgear_rx.rx_buf_cnt = 0;
  xgear_rx.cur_rx_buf = xgear_rx.rx_buf[xgear_rx.rx_buf_cnt];
  xgear_rx.prev_rx_buf = xgear_rx.cur_rx_buf;

  xgear_rx.msg_available = FALSE;

  xgear_rx.rxchar_cnt = 0;

  // Init Xgear serial port
  chEvtObjectInit(&eventXgearRx);

  // Port variables
  xgear_rx.overrun_error = 0;
  xgear_rx.noise_error = 0;
  xgear_rx.framing_error = 0;

  xgear_flag_tx = 0;

  // init mutex
  chMtxObjectInit(&mtx_xgear);

  // Lidar init
  xgear_lidar_init();

  //Payload and Isaac status init
  xgear_status_init();

  chThdCreateStatic(wa_thd_xgear_rx, sizeof(wa_thd_xgear_rx), HIGHPRIO-1, thd_xgear_rx, NULL);

#if PERIODIC_TELEMETRY
  register_periodic_telemetry(DefaultPeriodic, PPRZ_MSG_ID_XGEAR_INFO, send_xgear_info);
#endif
}


/**
 * Parse message
 * @param c received data
 */
void xgear_parse(uint8_t c) {
  switch(xgear_rx.status){
    case MsgSync0: // SYNC 0 = 0xBE, idx=0
      xgear_rx.idx = 0;
      if (c == XGEAR_SYNC0) {
        xgear_rx.msg_buf[xgear_rx.idx] = c;
        xgear_rx.idx++;
        xgear_rx.status = MsgSync1;
      } else {
        xgear_rx.hdr_error++;
      }
      break;
    case MsgSync1: // SYNC 1 = 0xEF, idx=1
      if (c == XGEAR_SYNC1) {
        xgear_rx.msg_buf[xgear_rx.idx] = c;
        xgear_rx.idx++;
        xgear_rx.status = MsgType;
      } else {
        xgear_rx.status = MsgSync0;
        xgear_rx.hdr_error++;
      }
      break;
    case MsgType: // TYPE= 1 or 2, idx = 2
      xgear_rx.type = c; // save for later
      xgear_rx.msg_buf[xgear_rx.idx] = c;
      xgear_rx.idx++;
      xgear_rx.status = MsgSize;
      break;
    case MsgSize: // SIZE depends on TYPE, idx = 3,4
      xgear_rx.msg_buf[xgear_rx.idx] = c;
      xgear_rx.idx++;
      if (xgear_rx.idx == 5) {
        xgear_rx.datalength =
            (uint16_t)(xgear_rx.msg_buf[xgear_rx.idx-2] << 8 | xgear_rx.msg_buf[xgear_rx.idx-1]);
        xgear_rx.status = MsgHdrChksum;
      }
      break;
    case MsgHdrChksum: // HDR CHKSUM, idx=5,6
      xgear_rx.msg_buf[xgear_rx.idx] = c;
      xgear_rx.idx++;
      if (xgear_rx.idx == 7) {
        xgear_rx.rx_chksum = (xgear_rx.msg_buf[xgear_rx.idx-2]<<8)+xgear_rx.msg_buf[xgear_rx.idx-1];
        xgear_rx.calc_chksum = calculate_checksum(xgear_rx.msg_buf+2, (uint16_t)(XGEAR_HEADER_LENGTH-4));

        if (xgear_rx.rx_chksum == xgear_rx.calc_chksum) {
          // header checksum OK, proceed to reading data
          xgear_rx.idx = 0;
          xgear_rx.status = MsgData;
        }
        else {
          // invalid checksum
          xgear_rx.status = MsgSync0;
          xgear_rx.chksm_error++;
        }
      }
      break;
    case MsgData: // Read data
      xgear_rx.msg_buf[xgear_rx.idx] =  c;
      xgear_rx.idx++;

      if (xgear_rx.idx == (xgear_rx.datalength+XGEAR_CHK_LEN)) {
        xgear_rx.rx_chksum = (xgear_rx.msg_buf[xgear_rx.idx-2]<<8)+xgear_rx.msg_buf[xgear_rx.idx-1];
        xgear_rx.calc_chksum = calculate_checksum(xgear_rx.msg_buf, xgear_rx.datalength);
        if (xgear_rx.rx_chksum == xgear_rx.calc_chksum) {
          // header checksum OK, proceed to reading msg
          xgear_rx.msg_cnt++;
          xgear_rx.msg_available = TRUE;
          xgear_rx.idx = 0;
        }
        else {
          // invalid checksum
          xgear_rx.msg_available = FALSE;
          xgear_rx.chksm_error++;
        }
        xgear_rx.status = MsgSync0;
      }
      break;
    default:
      xgear_rx.status = MsgSync0;
      xgear_rx.idx = 0;
      break;
  }
}

/**
 * Read parsed message
 * @param xgear
 */
void xgear_read_message(void){
  switch(xgear_rx.type){
    case XGEAR_MSG_TYPE_LIDAR:
      xgear_read_lidar(xgear_rx.msg_buf);
      break;
    case XGEAR_MSG_TYPE_MOVE_WAYPOINT:
      // NOTE: nothing at this moment
      break;
    case XGEAR_MSG_TYPE_ISAAC_STATUS:
      xgear_read_isaac_status(xgear_rx.msg_buf);
      break;
    case XGEAR_MSG_TYPE_PAYLOAD_STATUS:
      xgear_read_payload_status(xgear_rx.msg_buf);
      break;
    default:
      // unsupported message
      break;
  }
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
  static uint16_t hdr_chksum, dta_chksum;

  // header
  xgear_tx.msg_buf[0] = XGEAR_SYNC0;
  xgear_tx.msg_buf[1] = XGEAR_SYNC1;
  xgear_tx.msg_buf[2] = XGEAR_MSG_TYPE_SYSID;

  // header - size
  static uint16_t datalength = XGEAR_SYSID_PAYLOAD_LENGTH;
  xgear_tx.msg_buf[3] = (uint8_t)((datalength >> 8) & 0xFF); // MSB
  xgear_tx.msg_buf[4] = (uint8_t)(datalength & 0xFF); // LSB

  // header - checksum
  hdr_chksum = calculate_checksum(xgear_tx.msg_buf+2, (uint16_t)(XGEAR_HEADER_LENGTH-4));
  xgear_tx.msg_buf[5] = (uint8_t)(hdr_chksum >> 8);
  xgear_tx.msg_buf[6] = (uint8_t)(hdr_chksum & 0xFF);

  // DATA
  // index after the header
  xgear_tx.idx = XGEAR_HEADER_LENGTH;

  // timestamp
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ins_vn.timestamp, sizeof(float));
  xgear_tx.idx += sizeof(float);

  // YawPitchRoll [deg]
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ins_vn.ypr, 3*sizeof(float));
  xgear_tx.idx += 3*sizeof(float);

  // AngularRate
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ins_vn.gyro, 3*sizeof(float));
  xgear_tx.idx += 3*sizeof(float);

  // Position LLA
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ins_vn.pos_lla, 3*sizeof(double));
  xgear_tx.idx += 3*sizeof(double);

  // Velocity NED
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ins_vn.vel_ned, 3*sizeof(float));
  xgear_tx.idx += 3*sizeof(float);

  // Accel
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ins_vn.accel, 3*sizeof(float));
  xgear_tx.idx += 3*sizeof(float);

  // Tow
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &gps.tow, sizeof(uint32_t));
  xgear_tx.idx += sizeof(uint32_t);

  //num sats, uint8
  xgear_tx.msg_buf[xgear_tx.idx] = gps.num_sv;
  xgear_tx.idx++;

  //gps fix, uint8
  xgear_tx.msg_buf[xgear_tx.idx] = gps.fix;
  xgear_tx.idx++;

  //posU, float[3]
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ins_vn.pos_u, 3*sizeof(float));
  xgear_tx.idx += 3*sizeof(float);

  //velU, float
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ins_vn.vel_u, sizeof(float));
  xgear_tx.idx += sizeof(float);

  //linear acceleration imu-body frame, float [m/s^2]
  // Body acceleration without gravity
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ins_vn.lin_accel, 3*sizeof(float));
  xgear_tx.idx += 3*sizeof(float);

  //YprU, float[3]
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ins_vn.ypr_u, 3*sizeof(float));
  xgear_tx.idx += 3*sizeof(float);

  //instatus, uint16
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ins_vn.ins_status, 3*sizeof(uint16_t));
  xgear_tx.idx += sizeof(uint16_t);

  //Vel body, float [m/s]
  // The estimated velocity in the body (i.e. imu) frame, given in m/s.
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ins_vn.vel_body, 3*sizeof(float));
  xgear_tx.idx += 3*sizeof(float);

  // ap_time, float, [s]
  static float ap_time;
  ap_time = get_sys_time_float();
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &ap_time, sizeof(float));
  xgear_tx.idx += sizeof(float);

  // NUmber of commands
  xgear_tx.msg_buf[xgear_tx.idx] = (uint8_t)COMMANDS_NB;
  xgear_tx.idx++;

#if XGEAR_VTOL // VTOL CONFIGURATION
  // Servo #0
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &commands[0], sizeof(pprz_t));
  xgear_tx.idx += sizeof(pprz_t);

  // Servo #1
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &commands[1], sizeof(pprz_t));
  xgear_tx.idx += sizeof(pprz_t);

  // Servo #2
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &commands[2], sizeof(pprz_t));
  xgear_tx.idx += sizeof(pprz_t);

  // Servo #3
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &commands[3], sizeof(pprz_t));
  xgear_tx.idx += sizeof(pprz_t);

  // Servo #4 (Hexarotor only)
  if (COMMANDS_NB > 4) {
    memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &commands[4], sizeof(pprz_t));
  }
  else {
    static pprz_t dummy_cmd = 0;
    memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &dummy_cmd, sizeof(pprz_t));
  }
  xgear_tx.idx += sizeof(pprz_t);
#else // FIXEDWING CONFIGURATION
  // Command THROTTLE
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &commands[COMMAND_THROTTLE], sizeof(pprz_t));
  xgear_tx.idx += sizeof(pprz_t);

  // command ROLL
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &commands[COMMAND_ROLL], sizeof(pprz_t));
  xgear_tx.idx += sizeof(pprz_t);

  // command PITCH
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &commands[COMMAND_PITCH], sizeof(pprz_t));
  xgear_tx.idx += sizeof(pprz_t);

  // command YAW
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &commands[COMMAND_YAW], sizeof(pprz_t));
  xgear_tx.idx += sizeof(pprz_t);

  // command FLAPS
#ifdef COMMAND_FLAPS
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &commands[COMMAND_FLAPS], sizeof(pprz_t));
#else
  static pprz_t dummy_cmd = 0;
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &dummy_cmd, sizeof(pprz_t));
#endif
  xgear_tx.idx += sizeof(pprz_t);
#endif /* XGEAR VTOL */

  // alpha, float
  // NOTE: zero for now
  static float dummy_alpha = 0;
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &dummy_alpha, sizeof(float));
  xgear_tx.idx += sizeof(float);

  // beta, float
  // NOTE: zero for now
  static float dummy_beta = 0;
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &dummy_beta, sizeof(float));
  xgear_tx.idx += sizeof(float);

  // airspeed, float
  // NOTE: zero for now
  static float dummy_airspeed = 0;
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &dummy_airspeed, sizeof(float));
  xgear_tx.idx += sizeof(float);

  // ap_settings, uint16_t
  static uint16_t status = 0;
  set_status(&status);
  memcpy(&xgear_tx.msg_buf[xgear_tx.idx], &status, sizeof(uint16_t));
  xgear_tx.idx += sizeof(uint16_t);
  // END DATA


  // Payload Checksum
  dta_chksum = calculate_checksum(&(xgear_tx.msg_buf[XGEAR_HEADER_LENGTH]), (uint16_t)XGEAR_SYSID_PAYLOAD_LENGTH);
  xgear_tx.msg_buf[xgear_tx.idx] = (uint8_t)(dta_chksum >> 8);
  xgear_tx.idx++;
  xgear_tx.msg_buf[xgear_tx.idx] = (uint8_t)(dta_chksum & 0xFF);
  xgear_tx.idx++;

  // Send
  if (xgear_flag_tx == 0) {
    xgear_flag_tx = 1;
    uartStartSend(&XGEAR_PORT, (size_t)(xgear_tx.idx), xgear_tx.msg_buf);
  }

  xgear_tx.msg_cnt++;
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
