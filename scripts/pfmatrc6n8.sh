#!/bin/bash

export APPBLDNM=pfmatrc6n8

mkdir -p $APPBLDNM

echo "Profile for a ESP32-C6-WROOM-1-N8 composed Matter switch/light proxy.  Serial input enabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/blde32matr.sh --mainClass Embedded:Nada source/Nada.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
