#!/bin/bash


PORT="/dev/`ls /dev/ | grep cu.*usb`"

set -x

ampy --port ${PORT} run $1