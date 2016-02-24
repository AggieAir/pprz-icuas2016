ifneq ($(TARGET),hitl)
SIMULINK_FLAGS = -DSIMULINK_TYPE_H=\"modules/simulink/guidance_h_pid/guidance_simulink.h\"
$(TARGET).CFLAGS += -DGUIDANCE_SIMULINK=1 -DGUIDANCE_FLOAT=1
$(TARGET).CFLAGS += -DPORTABLE_WORDSIZES $(SIMULINK_FLAGS)
$(TARGET).srcs += modules/simulink/guidance_h_pid/guidance_simulink.c
$(TARGET).srcs += modules/simulink/guidance_h_pid/guidance_simulink_data.c
endif
