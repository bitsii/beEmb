#!/bin/bash

export APPBLDNM=pfn32blbbl

mkdir -p $APPBLDNM

echo "Profile for a Node32 Bulb." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp32noser.sh --emitFlag bleSup source/BLE.be --mainClass Embedded:RGBCWSh source/RGBCWC.be source/RGBCWSh.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
