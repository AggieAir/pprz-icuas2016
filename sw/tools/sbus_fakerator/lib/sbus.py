'''
Created on Dec 9, 2015

@author: kason
'''

import numpy as np

SBUS_NB_CHANNEL = 16
SBUS_BUFF_LENGTH = 22
SBUS_START_BYTE = 0x0f
SBUS_END_BYTE = 0x00
SBUS_BIT_PER_CHANNEL = 11
SBUS_BIT_PER_BYTE = 8

def sbus_decode(buff):
    decoded = [0 for x in range(SBUS_NB_CHANNEL)]
    byte_in_raw_buff = 0
    bit_in_raw_buff = 0
    channel = 0
    bit_in_channel = 0
    
    for c in range(SBUS_NB_CHANNEL * SBUS_BIT_PER_CHANNEL):
        # print channel
        if buff[byte_in_raw_buff] & (1 << bit_in_raw_buff):
            decoded[channel] |= (1 << bit_in_channel)
        
        bit_in_raw_buff += 1
        bit_in_channel += 1
        
        if(bit_in_raw_buff == SBUS_BIT_PER_BYTE):
            bit_in_raw_buff = 0
            byte_in_raw_buff += 1
        
        if(bit_in_channel == SBUS_BIT_PER_CHANNEL):
            bit_in_channel = 0
            channel += 1
    
    return decoded
    

def sbus_encode(buff):
    decoded = [0 for x in range(SBUS_BUFF_LENGTH)]
    channel = 0
    cur_byte = 0
    bit_in_byte = 0
    bit_in_channel = 0
    for x in range(SBUS_NB_CHANNEL * SBUS_BIT_PER_CHANNEL):
        if int(buff[channel]) & (1 << bit_in_channel):
            decoded[cur_byte] |= (1 << bit_in_byte)
        
        bit_in_channel += 1
        bit_in_byte += 1
        
        if(bit_in_byte == SBUS_BIT_PER_BYTE):
            bit_in_byte = 0
            cur_byte += 1
        
        if(bit_in_channel == SBUS_BIT_PER_CHANNEL):
            bit_in_channel = 0
            channel += 1
            
    return [SBUS_START_BYTE] + decoded + [0, SBUS_END_BYTE]
    
if __name__ == "__main__":
    control = [172, 72, 95, 0, 187, 199, 10, 86, 176, 130, 21, 172, 96, 5, 43, 88, 193, 138, 233, 133, 175, 123, 0, 0]
    print sbus_decode(control)
    print sbus_encode(sbus_decode(control))
