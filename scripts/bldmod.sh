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

rm -rf targets/mod/Base/target/cc

#--emitFlag relocMain

export CLASSPATH=../brace/target5/*
java -XX:-UsePerfData -XX:TieredStopAtLevel=1 -XX:+UseSerialGC be.BEL_Base -deployPath=targets/mod -buildPath=targets/mod --buildFile ../brace/build/tinyBase.txt --emitFlag embPlat --emitFlag noSmap --emitFlag noRfl --emitFlag moab --emitLang js --mainClass Test:TestHelloWorld source/test/TestMod.be

lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

CYC1=`date +%s`

cp targets/mod/Base/target/js/be/BEL_Base.js mod/fa/main.js

#mcconfig -d -m -p lin
#mcconfig -d -m -p simulator/nodemcu
#mcconfig -d -m -p esp/nodemcu

#time node ./targets/mod/Base/target/js/be/BEL_Base.js $*

#lae=$?;if [[ $lae -ne 0 ]]; then exit $lae; fi

CYC2=`date +%s`

expr \( $CYC2 - $CYC1 \)

