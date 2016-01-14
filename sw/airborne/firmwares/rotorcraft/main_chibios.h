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
 * @file main_chibios.h
 * Main file for ChibiOS/RT Paparazzi VTOL
 *
 * Includes both Paparazzi and ChibiOS files, threads are static.
 *
 * @author {Michal Podhradsky, Calvin Coopmans}
 */
#ifndef MAIN_CHIBIOS_H
#define MAIN_CHIBIOS_H

/* ChibiOS includes */
#include "ch.h"

/*
 * Thread Area Definitions
 */
#define CH_THREAD_AREA_HEARTBEAT 128
#define CH_THREAD_AREA_FAILSAFE 256
#define CH_THREAD_AREA_ELECTRICAL 256
#define CH_THREAD_AREA_RADIO_CONTROL 256
#define CH_THREAD_AREA_RADIO_EVENT 512
#define CH_THREAD_AREA_MODULES 1024
#define CH_THREAD_AREA_DOWNLINK_TX 1024
#define CH_THREAD_AREA_DOWNLINK_RX 1024
#define CH_THREAD_AREA_MONITOR 1024
#define CH_THREAD_AREA_BARO 512

/*
 * Thread declarations
 */
void thd_heartbeat(void *arg);
void thd_radio_control(void *arg);
void thd_electrical(void *arg);

#if PERIODIC_TELEMETRY
void thd_telemetry_tx(void *arg);
void thd_telemetry_rx(void *arg);
#endif

#if USE_BARO_BOARD
void thd_baro(void *arg);
#endif

void thd_modules_periodic(void *arg);
void thd_navigation(void *arg);
void thd_monitor(void *arg);

void spawn_threads(void);

void telemetry_periodic(void);
void main_init(void);
void failsafe_check(void);


#endif /* MAIN_CHIBIOS_H */