#!/bin/bash

export APPBLDNM=pfathlb0115wstbe

mkdir -p $APPBLDNM

echo "Profile for Athom 15W RGBCCT Bulb Strobe (LB01-RGBCW-15W-1400lm) " > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266noser.sh --mainClass Embedded:Strobe source/RGBC.be source/StrC.be source/Strobe.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
