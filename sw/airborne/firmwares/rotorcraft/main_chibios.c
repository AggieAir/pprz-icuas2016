/*
 * Copyright (C) 2015 AggieAir, A Remote Sensing Unmanned Aerial System for Scientific Applications
 * Utah State University, http://aggieair.usu.edu/
 *
 * Michal Podhradsky (michal.podhradsky@aggiemail.usu.edu)
 * Calvin Coopmans (c.r.coopmans@ieee.org)
 *
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
 * @file main_chibios.c
 * Main file for ChibiOS/RT Paparazzi VTOL
 *
 * Includes both Paparazzi and ChibiOS files, threads are static.
 *
 * @author {Michal Podhradsky, Calvin Coopmans}
 */
#define MODULES_C

#define ABI_C

#include <inttypes.h>
#include "mcu.h"
#include "mcu_periph/sys_time.h"
#include "led.h"

#include "subsystems/datalink/telemetry.h"
#include "subsystems/datalink/datalink.h"
#include "subsystems/datalink/downlink.h"
#include "subsystems/settings.h"

#include "subsystems/commands.h"
#include "subsystems/actuators.h"
#if USE_MOTOR_MIXING
#include "subsystems/actuators/motor_mixing.h"
#endif

#if USE_IMU
#include "subsystems/imu.h"
#endif
#if USE_GPS
#include "subsystems/gps.h"
#endif

#if USE_BARO_BOARD
#include "subsystems/sensors/baro.h"
PRINT_CONFIG_MSG_VALUE("USE_BARO_BOARD is TRUE, reading onboard baro: ", BARO_BOARD)
#endif

#include "subsystems/electrical.h"

#include "firmwares/rotorcraft/autopilot.h"

#include "subsystems/radio_control.h"

#include "firmwares/rotorcraft/stabilization.h"
#include "firmwares/rotorcraft/guidance.h"

#include "firmwares/rotorcraft/navigation.h"

#include "subsystems/ahrs.h"
#if USE_AHRS_ALIGNER
#include "subsystems/ahrs/ahrs_aligner.h"
#endif
#include "subsystems/ins.h"

#include "state.h"

#include "firmwares/rotorcraft/main_chibios.h"

#ifdef SITL
#include "nps_autopilot.h"
#endif

#include "generated/modules.h"
#include "subsystems/abi.h"

/* if PRINT_CONFIG is defined, print some config options */
PRINT_CONFIG_VAR(PERIODIC_FREQUENCY);

/* TELEMETRY_FREQUENCY is defined in generated/periodic_telemetry.h
 * defaults to 60Hz or set by TELEMETRY_FREQUENCY configure option in airframe file
 */
PRINT_CONFIG_VAR(TELEMETRY_FREQUENCY);

/* MODULES_FREQUENCY is defined in generated/modules.h
 * according to main_freq parameter set for modules in airframe file
 */
PRINT_CONFIG_VAR(MODULES_FREQUENCY);

#ifndef BARO_PERIODIC_FREQUENCY
#define BARO_PERIODIC_FREQUENCY 50
#endif
PRINT_CONFIG_VAR(BARO_PERIODIC_FREQUENCY);

#ifndef MONITOR_FREQUENCY
#define MONITOR_FREQUENCY 20
#endif
PRINT_CONFIG_VAR(MONITOR_FREQUENCY)

#ifndef ELECTRICAL_PERIODIC_FREQ
#define ELECTRICAL_PERIODIC_FREQ 10
#endif
PRINT_CONFIG_VAR(ELECTRICAL_PERIODIC_FREQ);

#ifndef RADIO_CONTROL_FREQ
#define RADIO_CONTROL_FREQ 60
#endif
PRINT_CONFIG_VAR(RADIO_CONTROL_FREQ);

#if USE_AHRS && USE_IMU && (defined AHRS_PROPAGATE_FREQUENCY)
#if (AHRS_PROPAGATE_FREQUENCY > PERIODIC_FREQUENCY)
#warning "PERIODIC_FREQUENCY should be least equal or greater than AHRS_PROPAGATE_FREQUENCY"
INFO_VALUE("it is recommended to configure in your airframe PERIODIC_FREQUENCY to at least ", AHRS_PROPAGATE_FREQUENCY);
#endif
#endif


#if PERIODIC_TELEMETRY
static void send_chibios_info(struct transport_tx *trans,
    struct link_device *dev)
{
  static uint16_t time_now = 0;
  time_now = chVTGetSystemTime() / CH_CFG_ST_FREQUENCY;

  // Mutex guard
  chMtxLock(&mtx_sys_time);

  pprz_msg_send_CHIBIOS_INFO(trans, dev, AC_ID, &core_free_memory, &time_now,
      &thread_counter, &cpu_frequency);

  // Mutex guard
  chMtxUnlock(&mtx_sys_time);
}
#endif

/**
 * HeartBeat & System Info
 *
 * Blinks LED and logs the cpu usage and other system info
 */
static THD_WORKING_AREA(wa_thd_heartbeat, CH_THREAD_AREA_HEARTBEAT);
void thd_heartbeat(void *arg)
{
  chRegSetThreadName("heartbeat");
  (void) arg;
  systime_t time = chVTGetSystemTime();
  static uint32_t last_idle_counter = 0;
  //static uint32_t last_nb_sec = 0;

  while (TRUE) {
    time += S2ST(1);

#ifdef SYS_TIME_LED
    LED_TOGGLE(SYS_TIME_LED);
#endif

    if (autopilot_in_flight) {
      autopilot_flight_time++;
#if defined DATALINK
      datalink_time++;
#endif
    }

    core_free_memory = chCoreGetStatusX();
    thread_counter = 0;

    thread_t *tp;
    tp = chRegFirstThread();
    do {
      thread_counter++;
      if (tp == chSysGetIdleThreadX()) {
#if CH_DBG_THREADS_PROFILING
        idle_counter = (uint32_t)tp->p_time;
#endif
      }
      tp = chRegNextThread(tp);
    } while (tp != NULL);

    // assume we call the counter once a second
    // so the difference in seconds is always one
    // NOTE: not perfectly precise due to low heartbeat priority -> +-5% margins
    // FIXME: add finer resolution than seconds?
    cpu_counter = (idle_counter - last_idle_counter);  // / ((nb_sec - last_nb_sec)/CH_CFG_ST_FREQUENCY);
    // / (sys_time.nb_sec - last_nb_sec);
    cpu_frequency = (1 - (float) cpu_counter / CH_CFG_ST_FREQUENCY) * 100;

    last_idle_counter = idle_counter;
    //last_nb_sec = sys_time.nb_sec;
    //last_nb_sec = nb_sec;

    chThdSleepUntil(time);
  }
}

/*
 * Electrical Periodic Thread
 *
 * Calls electrical_periodic()
 */
static THD_WORKING_AREA(wa_thd_electrical, CH_THREAD_AREA_ELECTRICAL);
void thd_electrical(void *arg)
{
  chRegSetThreadName("electrical");
  (void) arg;
  electrical_init();
  systime_t time = chVTGetSystemTime();
  while (TRUE) {
    time += US2ST(1000000 / ELECTRICAL_PERIODIC_FREQ);
    electrical_periodic();
    chThdSleepUntil(time);
  }
}

/**
 * Radio Control Periodic Thread
 *
 * Calls radio_control_periodic()
 */
static THD_WORKING_AREA(wa_thd_radio_control, CH_THREAD_AREA_RADIO_CONTROL);
void thd_radio_control(void *arg)
{
  chRegSetThreadName("radio_control");
  (void) arg;
  //radio_control_init();
  systime_t time = chVTGetSystemTime();
  while (TRUE) {
    time += US2ST(1000000 / RADIO_CONTROL_FREQ);
    radio_control_periodic_task();
    chThdSleepUntil(time);
  }
}

/**
 * Radio Control Event Thread
 *
 * Waits for EVT_PPM_FRAME event flag to be broadcasted,
 * then executes RadioControlEvent()
 *
 * @note: It is a nice example how to use event listeners.
 * Optionally after the frame is processed, another event can be
 * broadcasted, so it is possible to chain data processing (i.e. in AHRS)
 * Maybe a similar structure can be used for GPS events etc.
 *
 * after receiving EVT_PPM_FRAM and processing it, we can call
 * chEvtBroadcastFlags(&initializedEventSource, SOME_DEFINED_EVENT);
 * to propagate event further
 */
static THD_WORKING_AREA(wa_thd_radio_event, CH_THREAD_AREA_RADIO_EVENT);
void thd_radio_event(void *arg)
{
  chRegSetThreadName("radio_event");
  (void) arg;

  event_listener_t elRadioEvt;
  chEvtRegister(&eventRadioFrame, &elRadioEvt, EVT_RADIO_FRAME);
  eventflags_t rc_flags;

  while (TRUE) {
    chEvtWaitOne(EVENT_MASK(EVT_RADIO_FRAME));
    rc_flags = chEvtGetAndClearFlags(&elRadioEvt);
    if (rc_flags & EVT_RADIO_FRAME) {
      if (autopilot_rc)
      {
        RadioControlEvent(autopilot_on_rc_frame);
        chEvtBroadcastFlags(&eventRadioData, EVT_RADIO_DATA);
      }
    }
  }
}

//#if PERIODIC_TELEMETRY
/**
 * Telemetry TX thread
 */
static THD_WORKING_AREA(wa_thd_telemetry_tx, CH_THREAD_AREA_DOWNLINK_TX);
void thd_telemetry_tx(void *arg)
{
  (void) arg;
  chRegSetThreadName("telemetry_tx");
  systime_t time = chVTGetSystemTime();
  while (TRUE) {
    time += US2ST(1000000 / TELEMETRY_FREQUENCY);
#if RTOS_DEBUG
    LED_ON(3);
#endif
    telemetry_periodic();
#if RTOS_DEBUG
    LED_OFF(3);
#endif
    chThdSleepUntil(time);
  }
}

/**
 *  Telemetry RX thread
 *
 *  Replaces DatalinkEvent()
 */
static THD_WORKING_AREA(wa_thd_telemetry_rx, CH_THREAD_AREA_DOWNLINK_RX);
void thd_telemetry_rx(void *arg)
{
  chRegSetThreadName("telemetry_rx");
  (void) arg;
  event_listener_t elTelemetryRx;
  eventflags_t flags;
  chEvtRegisterMask(
      (event_source_t *) chnGetEventSource(
          (SerialDriver* ) DOWNLINK_DEVICE.reg_addr), &elTelemetryRx,
      EVENT_MASK(1));
  while (TRUE) {
    chEvtWaitOneTimeout(EVENT_MASK(1), S2ST(1));
    flags = chEvtGetAndClearFlags(&elTelemetryRx);
    // TODO: fix according to the EVENTs guide: http://chibios-book.readthedocs.org/en/latest/14_events/

    ch_uart_receive_downlink(DOWNLINK_DEVICE, flags, parse_pprz, &pprz_tp);
    if (pprz_tp.trans_rx.msg_received) {
      pprz_parse_payload(&(pprz_tp));
      pprz_tp.trans_rx.msg_received = FALSE;
      dl_parse_msg();
      dl_msg_available = FALSE;
    }

  }
}
//#endif /* PERIODIC_TELEMETRY */

/**
 * Modules periodic tasks
 */
static THD_WORKING_AREA(wa_thd_modules_periodic, CH_THREAD_AREA_MODULES);
void thd_modules_periodic(void *arg)
{
  chRegSetThreadName("modules_periodic");
  (void) arg;
  systime_t time = chVTGetSystemTime();
  while (TRUE) {
    time += US2ST(1000000/MODULES_FREQUENCY);
#if RTOS_DEBUG
    LED_ON(5);
#endif
    modules_periodic_task();
#if RTOS_DEBUG
    LED_OFF(5);
#endif
    chThdSleepUntil(time);
  }
}

/**
 * Monitoring Thread
 *
 * Runs Monitoring tasks, possibly also failsafe check if needed
 *
 * TODO: ChibiOS/RT failsafe check (hypervisor thread)
 */
static THD_WORKING_AREA(wa_thd_monitor, CH_THREAD_AREA_MONITOR);
void thd_monitor(void *arg)
{
  chRegSetThreadName("monitor_task");
  (void) arg;
  systime_t time = chVTGetSystemTime();
  while (TRUE) {
    time += US2ST(1000000 / MONITOR_FREQUENCY);
    failsafe_check();
    chThdSleepUntil(time);
  }
}

#if USE_BARO_BOARD
static THD_WORKING_AREA(wa_thd_baro, CH_THREAD_AREA_BARO);
void thd_baro(void *arg);

/**
 * Baro thread
 */
void thd_baro(void *arg)
{
  chRegSetThreadName("baro");
  (void) arg;

  systime_t time = chVTGetSystemTime();
  while (TRUE)
  {
    time += US2ST(1000000/BARO_PERIODIC_FREQUENCY);
    baro_periodic();
    chThdSleepUntil(time);
  }
}
#endif /* USE_BARO_BOARD */

/**
 * Initialize threads
 */
void spawn_threads(void)
{
  chThdCreateStatic(wa_thd_heartbeat, sizeof(wa_thd_heartbeat), LOWPRIO,
      thd_heartbeat, NULL);
  chThdCreateStatic(wa_thd_radio_event, sizeof(wa_thd_radio_event), NORMALPRIO,
      thd_radio_event, NULL);
  chThdCreateStatic(wa_thd_radio_control, sizeof(wa_thd_radio_control),
  NORMALPRIO, thd_radio_control, NULL);
  chThdCreateStatic(wa_thd_electrical, sizeof(wa_thd_electrical), LOWPRIO,
      thd_electrical, NULL);

#if PERIODIC_TELEMETRY
  chThdCreateStatic(wa_thd_telemetry_tx, sizeof(wa_thd_telemetry_tx), LOWPRIO,
      thd_telemetry_tx, NULL);
  chThdCreateStatic(wa_thd_telemetry_rx, sizeof(wa_thd_telemetry_rx), LOWPRIO,
      thd_telemetry_rx, NULL);
#endif /* PERIODIC_TELEMETRY */

  chThdCreateStatic(wa_thd_monitor, sizeof(wa_thd_monitor),
  HIGHPRIO, thd_monitor, NULL);

  chThdCreateStatic(wa_thd_modules_periodic, sizeof(wa_thd_modules_periodic),
  NORMALPRIO, thd_modules_periodic, NULL);

#if USE_BARO_BOARD
  chThdCreateStatic(wa_thd_baro, sizeof(wa_thd_baro),LOWPRIO, thd_baro, NULL);
#endif
}

/** mode to enter when RC is lost while using a mode with RC input (not AP_MODE_NAV) */
#ifndef RC_LOST_MODE
#define RC_LOST_MODE AP_MODE_FAILSAFE
#endif

void failsafe_check(void)
{
  if (radio_control.status == RC_REALLY_LOST&&
  autopilot_mode != AP_MODE_KILL &&
  autopilot_mode != AP_MODE_HOME &&
  autopilot_mode != AP_MODE_FAILSAFE &&
  autopilot_mode != AP_MODE_NAV) {
    autopilot_set_mode(RC_LOST_MODE);
  }

#if FAILSAFE_ON_BAT_CRITICAL
  if (autopilot_mode != AP_MODE_KILL &&
      electrical.bat_critical) {
    autopilot_set_mode(AP_MODE_FAILSAFE);
  }
#endif

#if USE_GPS
  gps_periodic_check();
  if (autopilot_mode == AP_MODE_NAV &&
      autopilot_motors_on &&
#if NO_GPS_LOST_WITH_RC_VALID
      radio_control.status != RC_OK &&
#endif
      GpsIsLost()) {
    autopilot_set_mode(AP_MODE_FAILSAFE);
  }

  if (autopilot_mode == AP_MODE_HOME &&
      autopilot_motors_on && GpsIsLost()) {
    autopilot_set_mode(AP_MODE_FAILSAFE);
  }
#endif

  autopilot_check_in_flight(autopilot_motors_on);
}

/**
 * Periodic telemetry
 * Equivalent of reporting_tast in fixedwing ap
 */
void telemetry_periodic(void)
{
  static uint8_t boot = TRUE;

  /* initialisation phase during boot */
  if (boot) {
#if DOWNLINK
    send_autopilot_version(&(DefaultChannel).trans_tx, &(DefaultDevice).device);
#endif
    boot = FALSE;
  }
  /* then report periodicly */
  else {
#if PERIODIC_TELEMETRY
    periodic_telemetry_send_Main(DefaultPeriodic, &(DefaultChannel).trans_tx, &(DefaultDevice).device);
#endif
  }
}

/**
 * Application main loop
 */
int main(void)
{
  // Init drives
  main_init();

  // Spawn threads
  spawn_threads();

#if PERIODIC_TELEMETRY
  register_periodic_telemetry(DefaultPeriodic, PPRZ_MSG_ID_CHIBIOS_INFO, send_chibios_info);
#endif

  // increase priority
  chThdSetPriority(HIGHPRIO);

  // small delay to have IO settle down
  chThdSleep(MS2ST(100));
  systime_t main_time = chVTGetSystemTime();

  while (TRUE) {
    main_time += US2ST(1000000 / PERIODIC_FREQUENCY);

#if RTOS_DEBUG
    LED_ON(2);
#endif

#if USE_IMU
    imu_periodic();
    ImuEvent();
#endif

    //FIXME: temporary hack, remove me
#ifdef InsPeriodic
    InsPeriodic();
    TODO("calling InsEvent, remove me..")
    InsEvent();
#endif

#if USE_GPS
    // TODO: remove this
    GpsEvent();
#endif

#if USE_BARO_BOARD
    // TODO: remove this
    BaroEvent();
#endif

#if FAILSAFE_GROUND_DETECT || KILL_ON_GROUND_DETECT
    // TODO: remove this
    DetectGroundEvent();
#endif

    // TODO: remove this
    modules_event_task();

    /* run control loops */
    autopilot_periodic();

    /*
     * Execute motor test function only if
     * in GROUND_CHECK block and NOT in flight
     *
     * NOTE: if we have 254 blocks and not "Ground Check" block
     * then the motor check function would exectute in the last block
     * But I dont want to add another condition check, so there is a compilation
     * check in autopilot.c
     */
    if ((nav_block == ap_ground_check_block) && (!autopilot_in_flight)) {
      autopilot_motor_test();
    }
    else {
      ap_motor_test_on = FALSE;
      SetActuatorsFromCommands(commands, autopilot_mode);
    }

#if RTOS_DEBUG
    LED_OFF(2);
#endif

    chThdSleepUntil(main_time);
  }
  return TRUE;
}

/**
 * Initialize drivers and subsystems
 */
void main_init(void)
{
  mcu_init();

  electrical_init();

  stateInit();

  actuators_init();
#if USE_MOTOR_MIXING
  motor_mixing_init();
#endif

  radio_control_init();

#if USE_BARO_BOARD
  baro_init();
#endif
#if USE_IMU
  imu_init();
#endif
#if USE_AHRS_ALIGNER
  ahrs_aligner_init();
#endif

#if USE_AHRS
  ahrs_init();
#endif

  ins_init();

#if USE_GPS
  gps_init();
#endif

  autopilot_init();

  modules_init();

  settings_init();

  mcu_int_enable();

#if DOWNLINK
  downlink_init();
#endif

#if USE_IMU
  // send body_to_imu from here for now
  AbiSendMsgBODY_TO_IMU_QUAT(1, orientationGetQuat_f(&imu.body_to_imu));
#endif
}
