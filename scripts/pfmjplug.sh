#!/bin/bash

export APPBLDNM=pfmjplug

mkdir -p $APPBLDNM

echo "Profile for the Martin Jerry Round Plug.  Button toggles the switch on +30ms hold and resets device on +9s hold. Serial input disabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266noser.sh --mainClass Embedded:SwitchButton source/SC.be source/BC.be source/SWBU.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
