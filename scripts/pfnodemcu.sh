#!/bin/bash

export APPBLDNM=pfnodemcu

mkdir -p $APPBLDNM

echo "Profile for a Esp8266 NodeMCU with a switch control on built in LED pin 16 and a dimmer control on built in LED pin 2 with most controls.  Serial input enabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266.sh --mainClass Embedded:Grande source/SC.be source/DC.be source/PC.be source/BC.be source/RGBC.be source/CWC.be source/RGBCWC.be source/StrC.be source/Grande.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
