#!/bin/bash

export APPBLDNM=pfaiyatoeh9w

mkdir -p $APPBLDNM

echo "Profile for Aiyato esp home (tas) 9w " > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266noser.sh --mainClass Embedded:LedL source/RGBC.be source/LedL.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
