// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:Files;
use Embedded:Aes as Crypt;
use Encode:Url as EU;
use Embedded:AppShell;

class Embedded:SwitchApp(AppShell) {

   makeSwInfo() {
     devType = "sw";
     devCode = "gsw";
     majVer = 1;
     minVer = 61;
   }

   loadStates() {
     slots {
       Int saswi;
       //on = 0, off = 255
       String on = "on";
       String off = "off";
       String getsw = "getsw";
       String setsw = "setsw";
       Int pini = 16; //2
       Int sapini;
       String sw;
     }
     saswi = config.getPos("sa.sw");
     //("saswi " + saswi).print();
     sapini = config.getPos("sa.pin");
     //("sapini " + sapini).print();

     String pins = config.get(sapini);
     if (TS.notEmpty(pins) && pins.isInteger) {
       pini = Int.new(pins);
       ("loaded pin " + pins).print();
     }

     String insw = config.get(saswi);
     if (TS.notEmpty(insw)) {
       sw = insw;
       doState(List.new().addValue("dostate").addValue("notpw").addValue(setsw).addValue(sw));
     }
   }

   configState(List cmdl) String {
     String pins = cmdl[3];
     unless (pins.isInteger) {
       return("error: pin must be an integer");
     }
     config.put(sapini, pins);
     pini = Int.new(pins);
     return("switch pin now " + pins);
   }

   doState(List cmdl) String {
     "in dostate".print();
     String scm = cmdl[2];
     if (scm == getsw) {
      if (TS.notEmpty(sw)) {
        return(sw);
        } else {
        return("undefined");
        }
     } elseIf (scm == setsw) {
        String insw = cmdl[3];
        if (insw == on) {
          on.print(); //write crashes without
          app.pinModeOutput(pini);
          app.analogWrite(pini, 0);
          sw = insw;
          config.put(saswi, on);
        } elseIf (insw == off) {
          off.print(); //write crashes without
          app.pinModeOutput(pini);
          app.analogWrite(pini, 255);
          sw = insw;
          config.put(saswi, off);
        }
     }
     return("ok");
   }
   
   clearStates() {

   }

}
