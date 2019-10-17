#!/bin/bash
I2C=0
SET="i2cset -y $I2C"
declare -a dz=("0x3f" "0x30" "0x5b" "0x79" "0x74" "0x6d" "0x6f" "0x38" "0xff" "0x7d")
echo "start at iic bus $I2C"

$SET 0x24 0x01

while true
do
    DATE4=$( date "+%H%M" )
    echo $DATE4
    
    $SET 0x34 ${dz[${DATE4:0:1}]}
    $SET 0x35 ${dz[${DATE4:1:1}]}
    $SET 0x36 ${dz[${DATE4:2:1}]}
    $SET 0x37 ${dz[${DATE4:3:1}]}
    sleep 1
done
