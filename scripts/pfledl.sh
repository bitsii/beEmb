#!/bin/bash

export APPBLDNM=pfledl

mkdir -p $APPBLDNM

echo "Profile for RGBLight.  PWM Control. Telnet debug enabled, reset by pin enabled. Serial input disabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266.sh --mainClass Embedded:LedL source/RGBC.be source/LedL.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
