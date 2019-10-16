# telemetry board for Dirt Rally

This project is to build a controller utility for developers and Dirt Rally fanboys.

Build Enviroment: OS:**Arch Linux**, **Dirt Rally on linux**, **GCC**, **Python3.7**

*No guarantee for Windows players*

## Intro

The Dirt Rally game provides with a UDP telemetry broadcasting port for users(you need to open it if you have never configured it before). This project contains four modules: the **subscriber** to grab data from the UDP broadcasting(socket), the **driver** to communicate with microcontroller, the **deivce** which includes only controlling flows for driving peripherals such as LED digits and huds, and the **examples**, which provide with well-build integrated demos.

## Configure Diry Rally UDP port **`IMPORTANT`**

for linux users, it is located at `~/.local/share/feral-interactive/DiRT Rally/VFS/User/AppData/Roaming/My Games/DiRT Rally/hardwaresettings/hardware_settings_config.xml`

configure the line like `<udp enabled="?" extradata="?" ip="?" port="?" delay="?" />` to `<udp enabled="true" extradata="3" ip="[IP]" port="[PORT]" delay="1" />`

The `[IP]` is the ip you want to broadcasting to, it is normally set to `localhost`.

The `[PORT]` is the port, it is set to `20777` by default.

## telemetry table

See this thread on [steamcommunity](https://steamcommunity.com/app/310560/discussions/0/481115363869500839/)

## Modules

#### subsriber `finished`

The Subscriber module only dedicated to recieve data from UDP port.

There is a dummy server to emulate the Diry Rally game so that developers do not have to open the game each time.

Subscriber is implemented in two languages, python code could be executed directly with `python3`, C code need to be compiled first, just use `gcc` to compile it.

Current subsscriber grab whole telemetry table while only velocity, max RPM, current RPM and gear was extracted from it.

#### driver `pending`

The driver is to communicate with microcontrollers. Note, if you broadcast to your linux boards on LAN, This step is not necessary. This part writes byte stream to the device via `/dev/ttyUSBx`. It is also implemented with both C and Python3.

#### device `developing`

Control flows for specified peripherals.

There are :
> 4 digites 7 segments driven by tm1650, controlled by i2c, could monitor velocity, elapsed time and distense

> dual-color 8x8 matrix driven by tm1640, controlled by GPIO, could monitor G-force offset, gear, percentage of rpm and tyre pressure(?)

> 5V DC voltmeter, controlled by PWM(Arduino analogWrite), use it best to monitor RPM(percentage) and Turbo(pity for not provided by Codemasters)

Functionalities were implemented with three platform : `Jetson NANO(RPi liked board)`, `Arduino Nano` and `STM32 blue pill`



#### example `pending`

Blank.
