#!/bin/bash

export APPBLDNM=pfgdfe32w

mkdir -p $APPBLDNM

echo "Profile for a Esp32 NodeMCU Df.  Serial input enabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/blde32gd.sh --mainClass Embedded:Nada source/Nada.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
