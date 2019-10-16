import serial
import time
import struct

PORT='/dev/ttyUSB0'

device = serial.Serial(PORT, 115200, timeout=25)

device.flush()
i=0
while True:
    print(struct.pack('>h', i))
    device.write(struct.pack('<h', i))
    device.flush()
    i=(i+1)%10000
    time.sleep(.01)
# first byte is the char of GEAR
# second byte is the percentage of power(4 bit)
# followed 3 byte is speed

'''
    display mapping
    |-gear -> alplabet
    |-speed
    | |-left most : 0 -> void
    | |-others : normal
    |-power
    | |-4bit -> 2x8 pillar
    | | | <5 -> green
    | | | >=5 -> red
'''
