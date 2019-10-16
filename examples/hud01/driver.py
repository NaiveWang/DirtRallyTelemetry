'''
    Contains velocity monitor
'''
import socket, struct, serial
from sys import stdout
# port & ip
HOST='localhost'
PORT=20777
SERIAL_PORT='/dev/ttyUSB0'

# gear map
GEAR={0.:'N', 1.:'1', 2.:'2', 3.:'3', 4.:'4', 5.:'5', 6.:'6', 7.:'7', 8.:'8', 9.:'9', 10.:'R'}
# position of f64
POS_GEAR=33
POS_RPM_MAX=63
POS_RPM_CURR=37
POS_V=7

RETRY_MAX=15
BUFF_SIZE=256

device = serial.Serial(SERIAL_PORT, 115200, timeout=25)
device.flush()

for i in range(RETRY_MAX):
    # the fallback loop
    try:
        # start to subscribe telemetry
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.bind((HOST, PORT))
        # read loop
        while True:
            b = sock.recv(BUFF_SIZE)
            if b:
                # receieved, process em'
                info = struct.unpack('64f', b[:256])
                stdout.write('GEAR:%s\tPOW:%lf%%\tV:%03dkph\r'%(GEAR[info[POS_GEAR]], info[POS_RPM_CURR]*100./info[POS_RPM_MAX], int(info[POS_V]*3.6)))
                stdout.flush()

                device.write(struct.pack('<hBB', int(info[POS_V]*3.6), int(info[POS_RPM_CURR]*256./info[POS_RPM_MAX]), int(info[POS_GEAR])))
                device.flush()
            else:
                # broken sock, fallback and reconnect
                raise Exception('broken sock')
    except Exception as E:
        print(E, ', retry %d'%i)
