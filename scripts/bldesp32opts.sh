#!/bin/bash

. ../beBase/scripts/bld5ext.sh

rm -rf targets/ard/Base/target/cc

#these are for rich connected stand alone devices esp32c3/c6

#basic - just casnic, update, mdns - any esp32
#
#$BEBLDR -deployPath=targets/ard -buildPath=targets/ard -cchImport=../beEmb/system/cc/be/BEAR_ESP32.hpp --emitFlag ccHs --buildFile build/embBase.txt --emitLang cc --singleCC true --emitFlag ccSgc --emitFlag ccNoRtti --emitFlag noWeb --emitFlag noMatr --emitFlag noSmc --emitFlag relocMain --emitFlag holdMain --emitFlag embPlat --emitFlag noSmap --emitFlag noRfl --emitFlag noAes --emitFlag bemdSmall --emitFlag bearEsp32 -cchImport=$BEEMB_CONF -cchImport=../beEmb/system/cc/be/BEAR_Imports.hpp -ccImport=../beEmb/system/cc/be/BEAR_Imports.cpp ../beBase/source/base/Uses.be source/ArdEmb.be source/ArdConfFs.be source/ArdWifi.be source/ArdSer.be source/ArdTcp.be source/ArdMdns.be source/ArdUpd.be source/SH.be $*

#ble - nimble setup - esp32c3 or esp32c6
#in the device .hpp config file must have #include <NimBLEDevice.h>
#
#$BEBLDR -deployPath=targets/ard -buildPath=targets/ard -cchImport=../beEmb/system/cc/be/BEAR_ESP32.hpp --emitFlag ccHs --buildFile build/embBase.txt --emitLang cc --singleCC true --emitFlag ccSgc --emitFlag ccNoRtti --emitFlag noWeb --emitFlag noMatr --emitFlag noSmc --emitFlag bleSup --emitFlag relocMain --emitFlag holdMain --emitFlag embPlat --emitFlag noSmap --emitFlag noRfl --emitFlag noAes --emitFlag bemdSmall --emitFlag bearEsp32 -cchImport=$BEEMB_CONF -cchImport=../beEmb/system/cc/be/BEAR_Imports.hpp -ccImport=../beEmb/system/cc/be/BEAR_Imports.cpp ../beBase/source/base/Uses.be source/ArdEmb.be source/ArdConfFs.be source/ArdWifi.be source/ArdSer.be source/ArdTcp.be source/ArdMdns.be source/BLE.be source/ArdUpd.be source/SH.be $*

#ble - nimble setup - df - esp32c3 or esp32c6
#in the device .hpp config file must have #include <NimBLEDevice.h>
#
$BEBLDR -deployPath=targets/ard -buildPath=targets/ard -cchImport=../beEmb/system/cc/be/BEAR_ESP32.hpp --emitFlag ccHs --buildFile build/embBase.txt --emitLang cc --singleCC true --emitFlag ccSgc --emitFlag ccNoRtti --emitFlag noWeb --emitFlag noMatr --emitFlag noSmc --emitFlag dfIs --emitFlag bleSup --emitFlag relocMain --emitFlag holdMain --emitFlag embPlat --emitFlag noSmap --emitFlag noRfl --emitFlag noAes --emitFlag bemdSmall --emitFlag bearEsp32 -cchImport=$BEEMB_CONF -cchImport=../beEmb/system/cc/be/BEAR_Imports.hpp -ccImport=../beEmb/system/cc/be/BEAR_Imports.cpp ../beBase/source/base/Uses.be source/ArdEmb.be source/ArdConfFs.be source/ArdWifi.be source/ArdSer.be source/ArdTcp.be source/ArdMdns.be source/Dfis.be source/BLE.be source/ArdUpd.be source/SH.be $*

#ble, matr - nimble setup, matter - esp32c6 8mb flash min doesn't work
#in the device .hpp config file must have #include <NimBLEDevice.h>
#
#$BEBLDR -deployPath=targets/ard -buildPath=targets/ard -cchImport=../beEmb/system/cc/be/BEAR_ESP32.hpp --emitFlag ccHs --buildFile build/embBase.txt --emitLang cc --singleCC true --emitFlag ccSgc --emitFlag ccNoRtti --emitFlag noWeb --emitFlag noSmc --emitFlag bleSup --emitFlag noMdns --emitFlag relocMain --emitFlag holdMain --emitFlag embPlat --emitFlag noSmap --emitFlag noRfl --emitFlag noAes --emitFlag bemdSmall --emitFlag bearEsp32 -cchImport=$BEEMB_CONF -cchImport=../beEmb/system/cc/be/BEAR_Imports.hpp -cchImport=../beEmb/system/cc/be/BEMT_Imports.hpp -ccImport=../beEmb/system/cc/be/BEAR_Imports.cpp ../beBase/source/base/Uses.be source/ArdEmb.be source/ArdConfFs.be source/ArdWifi.be source/ArdSer.be ../beBase/source/base/Float.be source/ArdMatr.be source/MMEP.be source/ArdTcp.be source/BLE.be source/ArdUpd.be source/SH.be $*

#removing updates - add "--emitFlag noUpd" and remove "source/ArdUpd.be"
#removing mdns - add "--emitFlag noMdns" and remove "source/ArdMdns.be"
#removing serial - add "--emitFlag noSer" and remove "source/ArdSer.be"
#adding matr - remove "--emitFlag noMatr" add "-cchImport=../beEmb/system/cc/be/BEMT_Imports.hpp" and
#  "../beBase/source/base/Float.be source/ArdMatr.be source/MMEP.be"
#adding mqtt direct - add "--emitFlag smcDm" and "source/SMC.be"

mkdir -p ard
cp ./targets/ard/Base/target/cc/be/*.?pp ard
