#!/bin/bash

./scripts/bldesp8266noser.sh --mainClass Embedded:Switch source/SC.be source/SW.be

mkdir -p ardswns

cp ard/* ardswns

mv ardswns/ard.ino ardswns/ardswns.ino
