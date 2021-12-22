#!/bin/bash

BIN=build/AvrTest
HEX=build/AvrTest.hex

avr-objcopy -O ihex -R .eeprom "$BIN" "$HEX"
avrdude -c arduino -P /dev/ttyUSB0 -p atmega328p -b 57600 -U flash:w:"$HEX"