#!/bin/bash

export APPBLDNM=pfrgbcwser

mkdir -p $APPBLDNM

echo "Profile for rgbcw led bulb " > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

#this is the serial profile for building and debugging, do not put on a real device, use sans "...ser.sh" instead
./scripts/bldesp8266.sh --mainClass Embedded:RGBCWSh source/RGBCWC.be source/RGBCWSh.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
