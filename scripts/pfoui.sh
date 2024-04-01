#!/bin/bash

export APPBLDNM=pfoui

mkdir -p $APPBLDNM

echo "Profile for own ui, serial enabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp8266.sh --mainClass Embedded:Oui source/TWCC.be source/OUI.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
