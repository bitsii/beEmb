#!/bin/bash

export APPBLDNM=pfaiya9wrgbw

mkdir -p $APPBLDNM

echo "Profile for Aiyato esp home (tas) 9w rgbw " > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266noser.sh --mainClass Embedded:RGBSh source/RGBC.be source/RGBSh.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
