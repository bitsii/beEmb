#!/bin/bash

export APPBLDNM=pfn32plg

mkdir -p $APPBLDNM

echo "Profile for an Esp32 Plug.  Button toggles the switch on +30ms hold and resets device on +30s hold." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp32opts.sh --mainClass Embedded:SwitchButton source/SC.be source/BC.be source/SWBU.be

#./scripts/bldesp32opts.sh --mainClass Embedded:Nada source/Nada.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
