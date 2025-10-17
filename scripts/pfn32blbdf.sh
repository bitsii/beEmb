#!/bin/bash

export APPBLDNM=pfn32blbdf

mkdir -p $APPBLDNM

echo "Profile for a Node32 Bulb." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp32noser.sh --emitFlag dfIs source/Dfis.be --mainClass Embedded:RGBCWSh source/RGBCWC.be source/RGBCWSh.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
