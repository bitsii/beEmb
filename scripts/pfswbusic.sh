#!/bin/bash

export APPBLDNM=pfswbusic

mkdir -p $APPBLDNM

echo "Profile for a typical Esp8266 NodeMCU with a switch wired to pin 5 (no resistor) and pin 16 and 2 both tied to a single switch control.  Button toggles the switch on +30ms hold and resets device on +10s hold" > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266noser.sh --mainClass Embedded:SwitchButtonIndicator source/SC.be source/BC.be source/SIC.be source/SWBUSIC.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
