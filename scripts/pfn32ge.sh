#!/bin/bash

export APPBLDNM=pfn32ge

mkdir -p $APPBLDNM

echo "Profile for a Esp32 Gateway to everything.  Serial input enabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/blde32ge.sh --mainClass Embedded:Nada source/Nada.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
