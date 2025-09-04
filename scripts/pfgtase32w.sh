#!/bin/bash

export APPBLDNM=pfgtase32w

mkdir -p $APPBLDNM

echo "Profile for a Casnic Esp32 Gateway to tasmota.  Serial input enabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/blde32gt.sh --mainClass Embedded:Nada source/Nada.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
