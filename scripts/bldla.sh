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

#--emitFlag relocMain

mono --debug ../brace/target5/BEX_E_mcs.exe -deployPath=targets/ard -buildPath=targets/ard --buildFile build/embBase.txt --emitLang cc --singleCC true --emitFlag ccSgc --emitFlag ccNoRtti --emitFlag relocMain --emitFlag holdMain --emitFlag embPlat --emitFlag noSmap --emitFlag noRfl -cchImport=../braceEmb/system/cc/be/BEAR_Imports.hpp -ccImport=../braceEmb/system/cc/be/BEAR_Imports.cpp --mainClass Embedded:LedApp ../brace/source/base/Uses.be source/ArdEmb.be source/ArdAes.be source/ArdUdp.be source/LA.be

lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

CYC1=`date +%s`

export CC=g++
export CPFLAGS="-std=c++11 -Wfatal-errors -ggdb"

#time g++ $CPFLAGS -DBEDCC_SGC=1 -o targets/ard/BEX_E_gn.exe ./targets/ard/Base/target/cc/be/BEL_Base.cpp

mkdir -p ard
cp ./targets/ard/Base/target/cc/be/*.?pp ard

lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

#time ./targets/ard/BEX_E_gn.exe

lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

CYC2=`date +%s`

expr \( $CYC2 - $CYC1 \)

