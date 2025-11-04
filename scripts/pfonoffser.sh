#!/bin/bash

export APPBLDNM=pfonoffser

mkdir -p $APPBLDNM

echo "Profile for on/off switches, plugs, etc.  Supports relays and optionally buttons." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

#this is the serial profile for building and debugging, do not put on a real device, use sans "...ser.sh" instead
./scripts/bldesp8266.sh --mainClass Embedded:SwitchButton source/SC.be source/BC.be source/SWBU.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
