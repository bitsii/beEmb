#!/bin/bash

. ../beBase/scripts/bld5ext.sh

rm -rf targets/ard/Base/target/cc

$BEBLDR -deployPath=targets/ard -buildPath=targets/ard -cchImport=../beEmb/system/cc/be/BEAR_ESP8266.hpp --buildFile build/embBase.txt --emitLang cc --singleCC true --emitFlag ccSgc --emitFlag ccNoRtti --emitFlag noWeb --emitFlag relocMain --emitFlag holdMain --emitFlag embPlat --emitFlag noSmap --emitFlag noRfl --emitFlag bemdSmall --emitFlag bearEsp8266 -cchImport=$BEEMB_CONF --emitFlag noSer -cchImport=../beEmb/system/cc/be/BEAR_Imports.hpp -ccImport=../beEmb/system/cc/be/BEAR_Imports.cpp ../beBase/source/base/Uses.be source/ArdEmb.be source/ArdConfFs.be source/ArdWifi.be source/ArdTcp.be source/ArdMdns.be source/ArdUpd.be source/SH.be $*

mkdir -p ard
cp ./targets/ard/Base/target/cc/be/*.?pp ard
