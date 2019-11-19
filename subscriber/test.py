'''
    This script test if your Diry Rally UDP Server has been started properly.
    the steam post of the UDP data format in detail : https://steamcommunity.com/app/310560/discussions/0/481115363869500839/

    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    for extradata = 3: output = 64 floats
    byteformat: little endian

    Position Info | Content Info
    No. Byte | Format Value

    0. 0 float Time
    1. 4 float Time of Current Lap
    2. 8 float Distance Driven on Current Lap
    3. 12 float Distance Driven Overall
    4. 16 float Position X
    5. 20 float Position Y
    6. 24 float Position Z
    7. 28 float Velocity (Speed) [m/s]
    8. 32 float Velocity X
    9. 36 float Velocity Y
    10. 40 float Velocity Z
    11. 44 float Roll Vector X
    12. 48 float Roll Vector Y
    13. 52 float Roll Vector Z
    14. 56 float Pitch Vector X
    15. 60 float Pitch Vector Y
    16. 64 float Pitch Vector Z
    17. 68 float Position of Suspension Rear Left
    18. 72 float Position of Suspension Rear Right
    19. 76 float Position of Suspension Front Left
    20. 80 float Position of Suspension Front Right
    21. 84 float Velocity of Suspension Rear Left
    22. 88 float Velocity of Suspension Rear Right
    23. 92 float Velocity of Suspension Front Left
    24. 96 float Velocity of Suspension Front Right
    25. 100 float Velocity of Wheel Rear Left
    26. 104 float Velocity of Wheel Rear Right
    27. 108 float Velocity of Wheel Front Left
    28. 112 float Velocity of Wheel Front Right
    29. 116 float Position Throttle
    30. 120 float Position Steer
    31. 124 float Position Brake
    32. 128 float Position Clutch
    33. 132 float Gear [0 = Neutral, 1 = 1, 2 = 2, ..., 10 = Reverse]
    34. 136 float G-Force Lateral
    35. 140 float G-Force Longitudinal
    36. 144 float Current Lap
    37. 148 float Speed of Engine [rpm / 10]
    38. 152 float ?
    39. 156 float ?
    40. 160 float ?
    41. 164 float ?
    42. 168 float ?
    43. 172 float ?
    44. 176 float ?
    45. 180 float ?
    46. 184 float ?
    47. 188 float ?
    48. 192 float ?
    49. 196 float ?
    50. 200 float ?
    51. 204 float Temperature Brake Rear Left ?
    52. 208 float Temperature Brake Rear Right ?
    53. 212 float Temperature Brake Front Left ?
    54. 216 float Temperature Brake Front Right ?
    55. 220 float ?
    56. 224 float ?
    57. 228 float ?
    58. 232 float ?
    59. 236 float ?
    60. 240 float Number of Laps in Total ?
    61. 244 float Length of Track in Total
    62. 248 float ?
    63. 252 float Maximum rpm / 10
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    this script is trying to show the velocity, and percentage of engine RPM, and code of GEAR

'''
import socket, struct
from sys import stdout
# port & ip
HOST='0.0.0.0'
PORT=20777
# gear map
GEAR={0.:'N', 1.:'1', 2.:'2', 3.:'3', 4.:'4', 5.:'5', 6.:'6', 7.:'7', 8.:'8', 9.:'9', 10.:'R'}
# position of f64
POS_GEAR=33
POS_RPM_MAX=63
POS_RPM_CURR=37
POS_V=7

RETRY_MAX=15
BUFF_SIZE=256


for i in range(RETRY_MAX):
    # the fallback loop
    try:
        # start to subscribe telemetry
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        sock.bind((HOST, PORT))
        # read loop
        while True:
            b = sock.recv(BUFF_SIZE)
            if b:
                # receieved, process em'
                info = struct.unpack('64f', b[:256])
                stdout.write('GEAR:%s\tPOW:%lf%%\tV:%03dkph\r'%(GEAR[info[POS_GEAR]], info[POS_RPM_CURR]*100./info[POS_RPM_MAX], int(info[POS_V]*3.6)))
                stdout.flush()
            else:
                # broken sock, fallback and reconnect
                raise Exception('broken sock')
    except Exception as E:
        print(E, ', retry %d'%i)
