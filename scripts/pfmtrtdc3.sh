#!/bin/bash

export APPBLDNM=pfmtrtdc3

mkdir -p $APPBLDNM

echo "Profile for a Esp32 With TDS to proxy mdns for Matr.  Serial input enabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/bldesp32.sh --mainClass Embedded:Grande source/SC.be source/DC.be source/PC.be source/BC.be source/RGBC.be source/CWC.be source/RGBCWC.be source/StrC.be source/Grande.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
