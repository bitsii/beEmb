#!/bin/bash

export APPBLDNM=pfathlb0115w

mkdir -p $APPBLDNM

echo "Profile for Athom 15W 1400lm RGBCCT Bulb (LB01-15) " > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266noser.sh --mainClass Embedded:LedL source/RGBC.be source/LedL.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
