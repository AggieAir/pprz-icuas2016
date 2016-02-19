ifneq ($(TARGET),hitl)
$(TARGET).CFLAGS += -DGUIDANCE_SIMULINK=TRUE
#$(TARGET).srcs += $(SRC_FIRMWARE)/guidance/guidance_simulink.c
endif
