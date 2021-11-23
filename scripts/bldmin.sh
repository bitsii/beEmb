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

rm -rf targets/min/Base/target/cc

#--emitFlag relocMain

mono --debug ../brace/target5/BEX_E_mcs.exe -deployPath=targets/min -buildPath=targets/min --buildFile build/embBase.txt --emitLang cc --singleCC true --emitFlag ccSgc --mainClass Test:TestHelloWorld ../brace/source/baseTest/TestHelloWorld.be

lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

CYC1=`date +%s`

export CC=g++
export CPFLAGS="-std=c++11 -Wfatal-errors -ggdb"

time g++ $CPFLAGS -DBEDCC_SGC=1 -o targets/min/BEX_E_gn.exe ./targets/min/Base/target/cc/be/BEL_Base.cpp

lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

time ./targets/min/BEX_E_gn.exe

lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

CYC2=`date +%s`

expr \( $CYC2 - $CYC1 \)

