# HUD01 Arduino Build

This is a tutorial for building a hud for Diry Rally

[video](https://youtu.be/vsle2yzDQVw)
![snapshot](https://github.com/NaiveWang/DirtRallyTelemetry/blob/master/examples/hud01/IMG20191016220319.jpg)

## Components

* [Arduino Nano/Uno and USB wire]() **necessary**
* [Dual Color 8x8 LED matrix with TM1640 controller]() **attachable**
* [3/4 digit 7/8 segments LED with TM1650/AIP650 controller]() **attachable**
* [5V DC voltmeter]() **attachable** *AC current noise issue with PWM*

## Enviroment Setup

* Linux
* Arduino IDE
* Python3, pyserial

## Wire Setup

Arduino uno is the same as nano

![image]()

* 8x8 LED

>**CLK -> D8**

>**DIN -> D7**

>**VCC -> 5V**

>**GND -> GND**

* 4 digits

>**SCL -> A5**

>**SDA -> A4**

>**VCC -> VCC**

>**GND -> GND**

* Voltmeter

> **+ -> D6**

> **- -> GND**

## Build Arduino & Start

0. Set up wire
1. Connect Arduino board to your computer.
2. Open, Compile & Upload `hud_dev` project. ( you may encounter a perimission issue, no fuss, just `chmod a+rw` to `/dev/ttyUSBx`port). If it was wired and set properly, the dots of the matrix should be all up either red or green execlusively and the 4 digits LED should be like `----`. ![snapshot](https://github.com/NaiveWang/DirtRallyTelemetry/blob/master/examples/hud01/IMG20191020115613.jpg)
3. Assume you have configured your Dirt game properly, configure Arduino port in `driver.py` and start it by `python driver.py` or `python3 driver.py`, now it started to listen on UDP port.

4. Open Dirt game, the hud start to read data while waiting for loading maps
