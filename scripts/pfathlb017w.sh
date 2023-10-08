#!/bin/bash

export APPBLDNM=pfathlb017w

mkdir -p $APPBLDNM

echo "Profile for Athom 7W 600lm RGBCCT Bulb (LB01-7W-B22) " > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266noser.sh --mainClass Embedded:LedL source/PC.be source/RGBC.be source/LedL.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
