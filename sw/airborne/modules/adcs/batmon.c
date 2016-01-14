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

#include "modules/adcs/batmon.h"

#include <string.h> // for memset

struct BatMon batmon;
int16_t bm_current_offset;
int16_t bm_current_sensitivity;

#if PERIODIC_TELEMETRY
#include "subsystems/datalink/telemetry.h"
static void send_batmon(struct transport_tx *trans, struct link_device *dev)
{
  uint16_t max_cell_volt = 0;
  uint16_t min_cell_volt = 65000;

  for(uint8_t i=0; i<BATTERY_CELL_NB; i++){
    if (batmon.cell_mvolts[i] > max_cell_volt) {
      max_cell_volt = batmon.cell_mvolts[i];
    }
    if (batmon.cell_mvolts[i] < min_cell_volt) {
      min_cell_volt = batmon.cell_mvolts[i];
    }
  }

  pprz_msg_send_BATTERY_MONITOR(trans, dev, AC_ID,
      &batmon.bus_current,
      &batmon.bus_voltage,
      &batmon.current,
      &batmon.stat_trans_bus,
      &batmon.stat_trans_port,
      &min_cell_volt,
      &max_cell_volt,
      BATTERY_CELL_NB,
      batmon.cell_mvolts);
}
#endif


/**
 *
 * Translates the channel number to the value
 * for address pointer register
 * Channels are numbered from 1 to 8
 * @param chan - desired channel
 * @return addres pointer Byte (see AD7997/8 datasheet)
 */
uint8_t batmon_get_address(uint8_t chan) {
  if ((chan>8) || (chan<1)){ // sanity check
    return 0x80;
  }
  static uint8_t adr[] = {0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0};
  return adr[chan-1];
}

/**
 * Init variables
 */
void batmon_init(void) {
  batmon.bus_current = 0;
  batmon.bus_trans.status = I2CTransDone;
  batmon.port_trans.status = I2CTransDone;
  batmon.stat_trans_port = batmon.port_trans.status;
  batmon.stat_trans_bus = batmon.bus_trans.status;
  batmon.bus_voltage = 0;
  batmon.current = 0;

  batmon.bus_status = BUS_CURRENT;
  batmon.cell_index = BATTERY_CELL_NB - 1;

  // zero the cell readings
  memset(batmon.cells,0,BATTERY_CELL_NB);

  //set the gains and cell position
  for(uint8_t i=0; i<BATTERY_CELL_NB; i++) {
    batmon.cellmap[i] = bm_cellmap[i];
    batmon.cellgains[i] = bm_cellgains[i];
  }

  //current sensor calibration
  bm_current_offset = BM_CURRENT_OFFSET;
  bm_current_sensitivity = BM_CURRENT_SENSITIVITY;

#if PERIODIC_TELEMETRY
  register_periodic_telemetry(DefaultPeriodic, PPRZ_MSG_ID_BATTERY_MONITOR, send_batmon);
#endif
}

/**
 * Read bus (current and bus voltage)
 */
void batmon_read_bus(void){
  static uint16_t data;
  switch (batmon.bus_status) {
    case BUS_CURRENT:
      batmon.bus_trans.buf[0] = batmon_get_address((uint8_t)BUS_CURRENT_CHANNEL);
      i2c_transceive(&BATMON_I2C_DEV, &batmon.bus_trans, BATMON_BUS_ADDR, 1, 2);
      data = (uint16_t) (batmon.bus_trans.buf[0] << 8 | batmon.bus_trans.buf[1]);
      batmon.cur_flag = batmon.bus_trans.buf[0] >> 7; // get status bit
      batmon.bus_current = data & 0xFFF; // get counts
      batmon.bus_current = (float)batmon.bus_current * BATMON_VREF_MULT; // convert to mV
      // convert to [A] - using a coarse calibration
      batmon.current = (((float)batmon.bus_current+BM_CURRENT_OFFSET))/BM_CURRENT_SENSITIVITY;
      if (batmon.current < 0) {
        batmon.current= 0;
      }
      //update electrical subsystem
      electrical.current = (int32_t)(batmon.current*1000); // current in mAs
      batmon.bus_status = BUS_VOLTAGE;
      break;
    case BUS_VOLTAGE:
      batmon.bus_trans.buf[0] = batmon_get_address((uint8_t)BUS_VOLTAGE_CHANNEL);
      i2c_transceive(&BATMON_I2C_DEV, &batmon.bus_trans, BATMON_BUS_ADDR, 1, 2);
      data = (uint16_t) (batmon.bus_trans.buf[0] << 8 | batmon.bus_trans.buf[1]);
      batmon.volt_flag = batmon.bus_trans.buf[0] >> 7; // get status bit
      batmon.bus_voltage = data & 0xFFF; // get counts
      batmon.bus_voltage = batmon.bus_voltage * BATMON_VREF_MULT; // convert to mV
      // convert sensed Voltage to the actual measured Voltage
      batmon.bus_voltage = batmon.bus_voltage * BATMON_VBUS_GAIN;
      batmon.bus_status = BUS_CURRENT;

      break;
    default:
      batmon.bus_status = BUS_CURRENT;
      break;
  }

  // update transaction status
  batmon.stat_trans_bus = batmon.bus_trans.status;
}

/**
 * Read battery ports in sequence
 */
void batmon_read_ports(void){
  static uint16_t data;

  // use our cell map to get correct channel address
  batmon.port_trans.buf[0] = batmon_get_address(batmon.cellmap[batmon.cell_index]);
  i2c_transceive(&BATMON_I2C_DEV, &batmon.port_trans, BATMON_PORT_ADDR, 1, 2);
  data = (uint16_t) (batmon.port_trans.buf[0] << 8 | batmon.port_trans.buf[1]);
  batmon.cells_flag[batmon.cell_index] = batmon.port_trans.buf[0] >> 7; // get status bit
  batmon.cells[batmon.cell_index] = data & 0xFFF; // get counts
  batmon.cells[batmon.cell_index] = batmon.cells[batmon.cell_index]*BATMON_VREF_MULT; // convert to mV
  // convert sensed Voltage to the actual measured Voltage
  batmon.cells[batmon.cell_index] = batmon.cells[batmon.cell_index] * batmon.cellgains[batmon.cell_index];

  // wrap around
  if (batmon.cell_index == 0) {
    //cell 0 has no offset
    batmon.cell_mvolts[batmon.cell_index] = batmon.cells[batmon.cell_index];
    batmon.cell_index = BATTERY_CELL_NB;
  }
  else
  {
    //calculate offsets from previous cell abs voltages
    batmon.cell_mvolts[batmon.cell_index] = batmon.cells[batmon.cell_index] - batmon.cells[batmon.cell_index - 1];
  }

  //decrement
  batmon.cell_index--;

  //update electrical subsystem
#if RTOS_DEBUG
// debug mode - use constant voltage
  electrical.vsupply = MAX_BAT_LEVEL*10;
#else
// normal operation
  //electrical.vsupply = batmon.cells[BATTERY_CELL_NB-1]/100; // mV to deci Volts
  electrical.vsupply = MAX_BAT_LEVEL*10;
#endif

  // update transaction status
  batmon.stat_trans_port = batmon.port_trans.status;
}
