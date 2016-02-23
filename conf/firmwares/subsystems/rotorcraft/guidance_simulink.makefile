ifneq ($(TARGET),hitl)
$(TARGET).CFLAGS += -DGUIDANCE_SIMULINK=1 -DGUIDANCE_FLOAT=1
$(TARGET).CFLAGS += -DPORTABLE_WORDSIZES
$(TARGET).srcs += modules/simulink/guidance_h_pid/guidance_simulink.c
$(TARGET).srcs += modules/simulink/guidance_h_pid/guidance_simulink_data.c
endif
