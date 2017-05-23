
# Wemos: Ex3 #

## Overview ##
The project demonstrates Wemos OLED shield usage

## Dependencies ##
- [SparkFun_Micro_OLED_Arduino_Library](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library)

## Platform IO notes ##

`platformio init -b d1_mini`
`platformio lib install git@github.com:sparkfun/SparkFun_Micro_OLED_Arduino_Library.git`
`platformio run -t upload`

## Open Serial port ##
`pio device monitor --port /dev/cu.wchusbserialfa130 --baud 115200`
or
`pio device monitor --port /dev/cu.SLAB_USBtoUART --baud 115200`
