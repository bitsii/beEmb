#!/bin/bash

. ../beBase/scripts/bld5ext.sh

rm -rf targets/ard/Base/target/cc

$BEBLDR -deployPath=targets/ard -buildPath=targets/ard -cchImport=../beEmb/system/cc/be/BEAR_ESP8266.hpp --emitFlag ccHs --buildFile build/embBase.txt --emitLang cc --singleCC true --emitFlag ccSgc --emitFlag ccNoRtti --emitFlag noWeb --emitFlag noMatr --emitFlag noSmc --emitFlag noTds --emitFlag relocMain --emitFlag holdMain --emitFlag embPlat --emitFlag noSmap --emitFlag noRfl --emitFlag noAes --emitFlag bemdSmall --emitFlag bearEsp8266 -cchImport=$BEEMB_CONF -cchImport=../beEmb/system/cc/be/BEAR_Imports.hpp -ccImport=../beEmb/system/cc/be/BEAR_Imports.cpp ../beBase/source/base/Uses.be source/ArdEmb.be source/ArdConfFs.be source/ArdWifi.be source/ArdSer.be source/ArdTcp.be source/ArdMdns.be source/ArdUpd.be source/SH.be $*

#--emitFlag noSer --emitFlag noUpd --emitFlag noTds --emitFlag noMdns --emitFlag noSmc source/TinyWeb.be source/ArdAes.be

mkdir -p ard
cp ./targets/ard/Base/target/cc/be/*.?pp ard
