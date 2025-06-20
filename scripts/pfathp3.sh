#!/bin/bash

export APPBLDNM=pfathp3

mkdir -p $APPBLDNM

echo "Profile for the Athom Plug V3 (US?).  Button toggles the switch on +30ms hold and resets device on +30s hold. Serial input disabled" > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp32noser.sh --mainClass Embedded:SwitchButton source/SC.be source/BC.be source/SWBU.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
