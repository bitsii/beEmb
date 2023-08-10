#!/bin/bash

./scripts/bldesp8266.sh --mainClass Embedded:SwitchAndDimmer source/SC.be source/DC.be source/SWDIM.be

mkdir -p ardswdim

cp ard/* ardswdim

mv ardswdim/ard.ino ardswdim/ardswdim.ino
