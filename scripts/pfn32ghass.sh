#!/bin/bash

export APPBLDNM=pfn32ghass

mkdir -p $APPBLDNM

echo "Profile for a Esp32 NodeMCU Mqtt Home Assistant Gateway  Serial input enabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/blde32gh.sh --mainClass Embedded:Nada source/Nada.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
