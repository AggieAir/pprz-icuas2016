# Top level makefile:
#  
PAPARAZZI_SRC ?= $(shell cd ../../..; pwd)
PAPARAZZI_HOME=$(PAPARAZZI_SRC)

# export the PAPARAZZI environment to sub-make
export PAPARAZZI_SRC
export PAPARAZZI_HOME

$(info ************  PAPARAZZI_HOME = $(PAPARAZZI_HOME) ************)

CXX		:= c++
CXXFLAGS 	:= -lpthread -lrt
INCLUDES	:= -I /usr/include/boost/ -I /usr/include/JSBSim/ -I ../../airborne/ -I ../../include -I ../nps
OBJECTS		:=  
LIBS        := -lboost_thread -lboost_system /usr/lib/libJSBSim.so
SRCS		:= ../../airborne/math/pprz_geodetic_double.c ../../airborne/math/pprz_geodetic_float.c \
			   ../../airborne/math/pprz_geodetic_wmm2015.c ../../airborne/math/pprz_algebra_double.c
# 
all: main.cpp
	$(CXX) main.cpp ${SRCS} -o hitl.bin -std=c++11 ${INCLUDES} ${CXXFLAGS} ${LIBS}
	#$(CXX) -ggdb3 main.cpp ${SRCS} -o bin/hitl -std=c++11 ${INCLUDES} ${CXXFLAGS} ${LIBS}

clean:
	rm hitl.bin
