# Hey Emacs, this is a -*- makefile -*-
#
# apogee_1.0_chibios.makefile
#
#

BOARD=lisa_mx
BOARD_VERSION=2.0
BOARD_DIR=$(BOARD)/v$(BOARD_VERSION)
BOARD_CFG=\"boards/$(BOARD_DIR)/board.h\"

ARCH=chibios
$(TARGET).ARCHDIR = $(ARCH)

RTOS=chibios

## FPU on F4
USE_FPU=yes
HARD_FLOAT=no

#$(TARGET).CFLAGS += -DSTM32F4

##############################################################################
# Architecture or project specific options
#
# Define project name here (target)
PROJECT = $(TARGET)
PROJECT_DIR=

# Project specific files and paths (see Makefile.chibios for details)
CHIBIOS_BOARD_PLATFORM = STM32F4xx/platform.mk
CHIBIOS_BOARD_PORT = ARMCMx/STM32F4xx/port.mk
CHIBIOS_BOARD_LINKER = STM32F407xG.ld

##############################################################################
# Compiler settings
#
MCU  = cortex-m4

# default flash mode is via usb dfu bootloader
# possibilities: DFU-UTIL, SWD, STLINK
FLASH_MODE ?= SWD

HAS_LUFTBOOT = FALSE

#
# default LED configuration
#
RADIO_CONTROL_LED  ?= 4
BARO_LED           ?= 5
AHRS_ALIGNER_LED   ?= 2
GPS_LED            ?= 3
SYS_TIME_LED       ?= 1

#
# default uart configuration
#
RADIO_CONTROL_SPEKTRUM_PRIMARY_PORT   ?= UART1
RADIO_CONTROL_SPEKTRUM_SECONDARY_PORT ?= UART5

MODEM_PORT ?= UART3
MODEM_BAUD ?= B57600

GPS_PORT ?= UART5
GPS_BAUD ?= B38400

#
# default actuator configuration
#
# you can use different actuators by adding a configure option to your firmware section
# e.g. <configure name="ACTUATORS" value="actuators_ppm/>
# and by setting the correct "driver" attribute in servo section
# e.g. <servo driver="Ppm">
#
ACTUATORS ?= actuators_pwm

