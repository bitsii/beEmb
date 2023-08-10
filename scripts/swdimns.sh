#!/bin/bash

./scripts/bldesp8266noser.sh --mainClass Embedded:SwitchAndDimmer source/SC.be source/DC.be source/SWDIM.be

mkdir -p ardswdimns

cp ard/* ardswdimns

mv ardswdimns/ard.ino ardswdimns/ardswdimns.ino
