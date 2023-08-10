#!/bin/bash

./scripts/bldesp8266noser.sh --mainClass Embedded:SwitchButtonIndicator source/SC.be source/BC.be source/SIC.be source/SWBUSIC.be

mkdir -p ardswbusicns

cp ard/* ardswbusicns

mv ardswbusicns/ard.ino ardswbusicns/ardswbusicns.ino
