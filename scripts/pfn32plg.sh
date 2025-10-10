#!/bin/bash

export APPBLDNM=pfn32plg

mkdir -p $APPBLDNM

echo "Profile for a Node32 Plug.  Button toggles the switch on +30ms hold and resets device on +30s hold." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp32.sh --mainClass Embedded:SwitchButton source/SC.be source/BC.be source/SWBU.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
