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
     devType = "switch";
     devCode = "gsw";
     majVer = 1;
     minVer = 42;
   }

   loadStates() {
     slots {
       String swf = "/lasw.txt";
       //on = 0, off = 255
       String on = "on";
       String off = "off";
       String getsw = "getsw";
       String setsw = "setsw";
       Int pini = 16; //2
       String pinif = "/lapin.txt";
       String sw;
     }
     if (files.exists(pinif)) {
       String pins = files.read(pinif);
       pini = Int.new(pins);
     }
     if (files.exists(swf)) {
       String insw = files.read(swf);
       sw = insw;
       doState(List.new().addValue(setsw).addValue(sw));
     }
   }

   configState(List cmdl) String {
     String pins = cmdl[3];
     unless (pins.isInteger) {
       return("error: pin must be an integer");
     }
     pini = Int.new(pins);
     files.write(pinif, pins);
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
          on.print();
          app.pinModeOutput(pini);
          app.analogWrite(pini, 0);
          sw = insw;
          //files.write(swf, on);
        } elseIf (insw == off) {
          off.print();
          app.pinModeOutput(pini);
          app.analogWrite(pini, 255);
          sw = insw;
          //files.write(swf, off);
        }
     }
     return("ok");
   }
   
   clearStates() {
     if (files.exists(swf)) {
       files.delete(swf);
     }
   }

}
