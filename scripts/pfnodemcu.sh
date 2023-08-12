#!/bin/bash

export APPBLDNM=pfnodemcu

mkdir -p $APPBLDNM

echo "Profile for a typical Esp8266 NodeMCU with a switch control on built in LED pin 16 and a dimmer control on built in LED pin 2" > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266.sh --mainClass Embedded:SwitchAndDimmer source/SC.be source/DC.be source/SWDIM.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
