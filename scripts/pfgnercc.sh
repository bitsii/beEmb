#!/bin/bash

export APPBLDNM=pfgnercc

mkdir -p $APPBLDNM

echo "Profile for empty initial conspec with conspect from config enabled.  Switch, Dimmer, Button, Indicator controls available.  Telnet debug enabled, teset by pin enabled. Serial input disabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266noser.sh --mainClass Embedded:SwitchDimmerButtonIndicator source/SC.be source/DC.be source/BC.be source/SIC.be source/SWDIMBUSIC.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
