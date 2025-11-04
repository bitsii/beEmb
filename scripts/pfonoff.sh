#!/bin/bash

export APPBLDNM=pfonoff

mkdir -p $APPBLDNM

echo "Profile for on/off switches, plugs, etc.  Supports relays and optionally buttons." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

#this is the profile for a real device, if you want to be able to interact over serial for development use the "...ser.sh" version instead.
./scripts/bldesp8266noser.sh --mainClass Embedded:SwitchButton source/SC.be source/BC.be source/SWBU.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
