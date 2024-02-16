#!/bin/bash

export APPBLDNM=pfndc

mkdir -p $APPBLDNM

echo "Profile for a Esp8266 NodeMCU with dynamic configuration and most controls. Serial input enabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266.sh --emitFlag dynConf --mainClass Embedded:Grande source/SC.be source/DC.be source/BC.be source/RGBC.be source/CWC.be source/RGBCWC.be source/StrC.be source/Grande.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
