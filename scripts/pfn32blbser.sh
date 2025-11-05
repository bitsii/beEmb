#!/bin/bash

export APPBLDNM=pfn32blbser

mkdir -p $APPBLDNM

echo "Profile for an Esp32C3 Bulb." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp32.sh --mainClass Embedded:RGBCWSh source/RGBCWC.be source/RGBCWSh.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
