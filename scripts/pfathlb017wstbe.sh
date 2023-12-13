#!/bin/bash

export APPBLDNM=pfathlb017wstbe

mkdir -p $APPBLDNM

echo "Profile for Athom 7W RGBCCT Bulb Strobe " > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266noser.sh --mainClass Embedded:Strobe source/SC.be source/DC.be source/StrDC.be source/Strobe.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
