#!/bin/bash

export APPBLDNM=pfn32matr

mkdir -p $APPBLDNM

echo "Profile for a Esp32 NodeMCU composed Matter switch/light proxy.  Serial input enabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/blde32matr.sh --mainClass Embedded:Switch source/SC.be source/SW.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
