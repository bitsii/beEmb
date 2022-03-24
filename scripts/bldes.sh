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

rm -rf targets/es/Base/target/cc

#--emitFlag relocMain

export CLASSPATH=../brace/target5/*
java -XX:-UsePerfData -XX:TieredStopAtLevel=1 -XX:+UseSerialGC be.BEL_Base -deployPath=targets/es -buildPath=targets/es --buildFile build/embBase.txt --emitFlag embPlat --emitFlag noSmap --emitFlag noRfl --emitLang js -mainClass=Test:TestBlink source/test/TestBlinkEs.be

lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

CYC1=`date +%s`

#uglifyjs ./targets/es/Base/target/js/be/BEL_Base.js > ./targets/es/Base/target/js/be/BEL_Base_ug.js

#time node ./targets/es/Base/target/js/be/BEL_Base.js $*

lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

CYC2=`date +%s`

expr \( $CYC2 - $CYC1 \)

