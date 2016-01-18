# Hey Emacs, this is a -*- makefile -*-
ifneq ($(TARGET),hitl)
$(TARGET).CFLAGS += -DUSE_NAVIGATION
$(TARGET).srcs += $(SRC_FIRMWARE)/navigation.c
$(TARGET).srcs += subsystems/navigation/waypoints.c
$(TARGET).srcs += subsystems/navigation/common_flight_plan.c
endif
