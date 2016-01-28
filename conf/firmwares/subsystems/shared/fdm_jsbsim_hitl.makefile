# Hey Emacs, this is a -*- makefile -*-

#
# SITL Simulator
#

JSBSIM_ROOT ?= /opt/jsbsim
JSBSIM_INC = $(JSBSIM_ROOT)/include/JSBSim
JSBSIM_LIB = $(JSBSIM_ROOT)/lib

#SRC_FIRMWARE=firmwares/fixedwing

SRC_BOARD=boards/$(BOARD)

hitl.ARCHDIR = sim

# include Makefile.nps instead of Makefile.sim
hitl.MAKEFILE = hitl

# add normal ap and fbw sources define in autopilot.makefile
#hitl.CFLAGS  += $(fbw_CFLAGS) $(ap_CFLAGS)
#hitl.srcs    += $(fbw_srcs) $(ap_srcs)

#hitl.CFLAGS  += -DSITL -DUSE_NPS
hitl.CFLAGS  += $(shell pkg-config glib-2.0 --cflags)
hitl.LDFLAGS += $(shell pkg-config glib-2.0 --libs) -lm -lglibivy $(shell pcre-config --libs) -lgsl -lgslcblas
#hitl.CFLAGS  += -I$(SRC_FIRMWARE) -I$(SRC_BOARD) -I$(PAPARAZZI_SRC)/sw/simulator -I$(PAPARAZZI_SRC)/sw/simulator/nps -I$(PAPARAZZI_HOME)/conf/simulator/nps
hitl.LDFLAGS += $(shell sdl-config --libs)

# use the paparazzi-jsbsim package if it is installed, otherwise look for JSBsim under /opt/jsbsim
JSBSIM_PKG ?= $(shell pkg-config JSBSim --exists && echo 'yes')
ifeq ($(JSBSIM_PKG), yes)
	hitl.CFLAGS  += $(shell pkg-config JSBSim --cflags)
	hitl.LDFLAGS += $(shell pkg-config JSBSim --libs)
else
	JSBSIM_PKG = no
	hitl.CFLAGS  += -I$(JSBSIM_INC)
	hitl.LDFLAGS += -L$(JSBSIM_LIB) -lJSBSim
endif

#
# add the simulator directory to the make searchpath
#
VPATH = $(PAPARAZZI_SRC)/sw/simulator

NPSDIR = hitl
hitl.srcs += $(NPSDIR)/main.cpp
hitl.srcs += math/pprz_geodetic_wmm2015.c
