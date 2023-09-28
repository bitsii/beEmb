#!/bin/bash

export APPBLDNM=pfrgbl

mkdir -p $APPBLDNM

echo "Profile for RGBLight.  PWM Control. Telnet debug enabled, reset by pin enabled. Serial input disabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266noser.sh --mainClass Embedded:RGBL source/PC.be source/RGBL.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
