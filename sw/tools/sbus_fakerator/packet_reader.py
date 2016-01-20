import serial
import struct

from lib import sbus



NUMBER_OF_CHANNELS = 16
SBUS_PACKET_LENGTH = 25
SBUS_BUFF_LENGTH = 22
SBUS_START_BYTE = 0x0f
SBUS_END_BYTE = 0x00

SBUS_UNINT_STATE = 0
SBUS_READ_STATE = 1
SBUS_ERROR_STATE = 2




# Especifies the port where the SBUS (RC Receiver) is connected

packet = []
read_packet_state = 0
ready_out = False

#debug variables
packet_number = 0


def packet_readerator(byte):
    global read_packet_state
    global packet
    global ready_out
    #Check if input is recieved
    if byte == None:
        raise IOError("No Controller Input")

    if byte == SBUS_START_BYTE and read_packet_state== SBUS_UNINT_STATE:
        packet = []
        read_packet_state = SBUS_READ_STATE

    if read_packet_state == SBUS_READ_STATE:
        packet.append(byte)

        if byte == SBUS_END_BYTE and len(packet) == SBUS_PACKET_LENGTH:
            read_packet_state = SBUS_UNINT_STATE
            ready_out = True
        #if we're bigger than packet length, set to error state
        elif len(packet) == SBUS_PACKET_LENGTH:
            read_packet_state = SBUS_ERROR_STATE

    #if we are in an error state, wait till end of packet is recieved, then reset
    if read_packet_state == SBUS_ERROR_STATE:
        if byte == SBUS_END_BYTE:
            read_packet_state=SBUS_UNINT_STATE


def loop(ser_rc):
    global ready_out
    while True:
        things = struct.unpack('<B', ser_rc.read(1))[0]
        #send the values to the callback function
        packet_readerator(things)
        #print self.read_packet_state
        if ready_out is True:
            print "O: {}".format(packet)
            ready_out = False
