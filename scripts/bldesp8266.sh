#!/bin/bash

una=`uname -a`
case "$una" in
  *Msys*)
    export MAKNAME="mingw32-make"
    ;;
  *)
    export MAKNAME="make"
    ;;
esac

rm -rf targets/ard/Base/target/cc

export CLASSPATH=../beBase/target5/*
java -XX:-UsePerfData -XX:TieredStopAtLevel=1 -XX:+UseSerialGC be.BEL_Base -deployPath=targets/ard -buildPath=targets/ard --buildFile build/embBase.txt --emitLang cc --singleCC true --emitFlag ccSgc --emitFlag ccNoRtti --emitFlag noMqtt --emitFlag noWeb --emitFlag relocMain --emitFlag holdMain --emitFlag embPlat --emitFlag noSmap --emitFlag noRfl --emitFlag bemdSmall --emitFlag embEsp8266 -cchImport=$BEEMB_CONF -cchImport=../beEmb/system/cc/be/BEAR_Imports.hpp -ccImport=../beEmb/system/cc/be/BEAR_Imports.cpp ../beBase/source/base/Uses.be source/ArdEmb.be source/ArdConf.be source/ArdWifi.be source/ArdSer.be source/ArdTcp.be source/ArdMdns.be source/ArdUpd.be source/SH.be $*

#--emitFlag noSer --emitFlag noUpd --emitFlag noMqtt source/TinyWeb.be source/ArdMqtt.be

mkdir -p ard
cp ./targets/ard/Base/target/cc/be/*.?pp ard
