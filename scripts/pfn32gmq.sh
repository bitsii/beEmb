#!/bin/bash

export APPBLDNM=pfn32gmq

mkdir -p $APPBLDNM

echo "Profile for a Esp32 NodeMCU Mqtt Gateway.  Serial input enabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/blde32gm.sh --mainClass Embedded:Nada source/Nada.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
