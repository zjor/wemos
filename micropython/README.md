# How to install #

- install esptool
`sudo pip install esptool`

- erase flash
`esptool.py --port /dev/cu.wchusbserial1410 erase_flash`

- deploy the firmware (download)[http://micropython.org/download#esp8266]
`esptool.py --port /dev/cu.wchusbserial1410 --baud 460800 write_flash --flash_size=detect 0 esp8266-20170612-v1.9.1.bin`

- check deployment via serial monitor
`pio device monitor --baud 115200`
And issue a command `print("hello")`

- install (ampy)[https://learn.adafruit.com/micropython-basics-load-files-and-run-code/install-ampy]
`sudo pip install adafruit-ampy`

- check ampy installation and connection with board
`ampy --port /dev/cu.wchusbserial1410 ls`