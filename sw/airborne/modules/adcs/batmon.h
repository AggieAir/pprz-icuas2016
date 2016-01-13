/*
 * Copyright (C) 2008-2015 The Paparazzi Team
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

/*
 * driver for ADC AD7997 on a custom made board
 * 2012, Utah State University, http://aggieair.usu.edu/
 * Author: Michal Podhradsky, michal.podhradsky@aggiemail.usu.edu
 */

#ifndef BATMON_H
#define BATMON_H

#include "std.h"
#include "mcu_periph/i2c.h"
#include "mcu_periph/sys_time.h"
#include "subsystems/electrical.h"

// default i2c device
#ifndef BATMON_I2C_DEV
#define BATMON_I2C_DEV i2c2
#endif

// define bit resolution
#ifndef AD7998_BIT_RES
#define AD7998_BIT_RES 12
#endif

// default reference (5 Volts)
#ifndef AD7998_VREF
#define AD7998_VREF 5000 // mV
#endif

// reading multiplier
#define BATMON_VREF_MULT AD7998_VREF/(1<<AD7998_BIT_RES)

// address is 01000110 (AS=GND), 01001000 (AS=VDD), 01000000 (AS=FLOAT)
#ifndef BATMON_BUS_ADDR
#define BATMON_BUS_ADDR 0x46
#endif
#ifndef BATMON_PORT_ADDR
#define BATMON_PORT_ADDR 0x40
#endif
// 0x44 for combiner board -> AD7998-0 (OK)
// 0x40 on the Power Board -> AD7997-1 float
// 0x46 on the Power Board -> AD7997-1 GND (OK)

// we are using 6 cells by default
#ifndef BATTERY_CELL_NB
#define BATTERY_CELL_NB 6
#endif

/* cell ADC gains (in mV)
 * Fill in gains from your voltage divider5.0/339.0
 * example: 3.3k and 10k divider gives equation
 * Vsense = (3.3)/13.3 * Vin = 0.24*Vin
 * Vin = 1/0.24 * Vsense
 * Vin = 4.03 * Vsense
 * Gain is then 4.03 (counts are already taken in account)
 */
#define GAIN_CELL_1 1.001
#define GAIN_CELL_2 2.011
#define GAIN_CELL_3 3.027
#define GAIN_CELL_4 4.063
#define GAIN_CELL_5 4.217
#define GAIN_CELL_6 4.973


static const float bm_cellgains[] = {GAIN_CELL_1, GAIN_CELL_2,
    GAIN_CELL_3, GAIN_CELL_4, GAIN_CELL_5, GAIN_CELL_6};


/*
 * Cell map - which cell is which channel
 * Channels are 1-indexed, ie.e. Channel 1 - Channel 8
 * Cells are 0-indexed (because of their position in the array)
 * So cell at bm_cellmap[0] is the first cell etc.
 */
static const uint8_t bm_cellmap[] = {2,4,6,8,5,7};

// define channels
#ifndef BUS_CURRENT_CHANNEL
#define BUS_CURRENT_CHANNEL 2
#endif
#ifndef BUS_VOLTAGE_CHANNEL
#define BUS_VOLTAGE_CHANNEL 4
#endif

/*
 * Define bus voltage gain based on
 * values of voltage divider at
 * power board
 */
#ifndef BATMON_VBUS_GAIN
#define BATMON_VBUS_GAIN 4.953980661
#endif

/*
 * Define current sensor calibration
 * include default values
 * See datasheet for your current sensor
 * to get the typical values
 */
#ifndef BM_CURRENT_OFFSET //mV
#define BM_CURRENT_OFFSET -120
#endif
#ifndef BM_CURRENT_SENSITIVITY //mV
#define BM_CURRENT_SENSITIVITY 25.6
#endif

// can be tuned via datalink
extern int16_t bm_current_offset;
extern int16_t bm_current_sensitivity;

enum BusStatus {
  BUS_CURRENT,
  BUS_VOLTAGE,
};

struct BatMon {
  // transactions
  struct i2c_transaction bus_trans;
  uint8_t stat_trans_bus;
  enum BusStatus bus_status;
  struct i2c_transaction port_trans;
  uint8_t stat_trans_port;
  uint8_t cell_index;

  // raw readings (bus)
  uint16_t bus_current;
  uint16_t bus_voltage;
  uint8_t cur_flag;
  uint8_t volt_flag;

  // raw readings (port)
  uint8_t cellmap[BATTERY_CELL_NB];
  float cellgains[BATTERY_CELL_NB];
  uint16_t cells[BATTERY_CELL_NB];
  uint8_t cells_flag[BATTERY_CELL_NB];

  //processed readings (port)
  uint16_t cell_mvolts[BATTERY_CELL_NB];

  // processed readings (bus)
  float current;

};

extern struct BatMon batmon;

void batmon_init(void);
void batmon_read_bus(void);
void batmon_read_ports(void);
uint8_t batmon_get_address(uint8_t channel);

#endif /* BATMON_H */
