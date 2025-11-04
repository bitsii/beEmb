#!/bin/bash

export APPBLDNM=pfrgbcw

mkdir -p $APPBLDNM

echo "Profile for rgbcw led bulb " > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

#this is the profile for a real device, if you want to be able to interact over serial for development use the "...ser.sh" version instead.
./scripts/bldesp8266noser.sh --mainClass Embedded:RGBCWSh source/RGBCWC.be source/RGBCWSh.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
