#!/bin/bash

export APPBLDNM=pfmatrqtpo

mkdir -p $APPBLDNM

echo "Profile for a Esp32 QT PY Pico composed Matter switch/light proxy.  Serial input enabled." > $APPBLDNM/README.txt

export BEEMB_CONF=../beEmb/confs/${APPBLDNM}.hpp

./scripts/blde32matr.sh --mainClass Embedded:Nada source/Nada.be

cp ard/* $APPBLDNM

mv $APPBLDNM/ard.ino $APPBLDNM/${APPBLDNM}.ino
