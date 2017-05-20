
# Wemos: Ex3 #

## Overview ##
The project demonstrates Wemos OLED shield usage

## Dependencies ##
- [Adafruit_SSD1306](git@github.com:mcauser/Adafruit_SSD1306.git)

## Platform IO notes ##

`platformio init -b d1_mini`
`platformio lib install git@github.com:mcauser/Adafruit_SSD1306.git`
`platformio lib install git@github.com:adafruit/Adafruit-GFX-Library.git`
`platformio run -t upload`
`pio device monitor --port /dev/cu.wchusbserialfa130 --baud 115200`
