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

rm -rf targets/eidf/Base/target/cc

#--emitFlag relocMain

export CLASSPATH=../brace/target5/*
java -XX:-UsePerfData -XX:TieredStopAtLevel=1 -XX:+UseSerialGC be.BEL_Base -deployPath=targets/eidf -buildPath=targets/eidf --buildFile build/embBase.txt --emitLang cc --singleCC true --emitFlag ccSgc --emitFlag ccNoRtti --emitFlag relocMain --emitFlag embPlat --emitFlag noSmap --emitFlag noRfl -cchImport=../braceEmb/system/cc/be/BEEI_Imports.hpp -ccImport=../braceEmb/system/cc/be/BEEI_Imports.cpp --mainClass Test:TestBlink source/test/TestBlinkEWEIDF.be

lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

CYC1=`date +%s`

export CC=g++
export CPFLAGS="-std=c++11 -Wfatal-errors -ggdb"

#time g++ $CPFLAGS -DBEDCC_SGC=1 -o targets/eidf/BEX_E_gn.exe ./targets/eidf/Base/target/cc/be/BEL_Base.cpp

mkdir -p ~/esp/beblink_cxx/main
cp ./targets/eidf/Base/target/cc/be/*.?pp ~/esp/beblink_cxx/main

lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

#time ./targets/eidf/BEX_E_gn.exe

lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

CYC2=`date +%s`

expr \( $CYC2 - $CYC1 \)

