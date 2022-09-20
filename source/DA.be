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

class Embedded:DimmerApp(AppShell) {

   makeSwInfo() {
     devType = "dimmer";
     devCode = "gdi";
     majVer = 1;
     minVer = 59;
   }

   loadStates() {
     slots {
       String setlvll = "setlvl";
       String setrlvll = "setrlvl";
       //on = 0, off = 255
       Int pini = 16; //2
       String stf = "/dast.txt";
       String pinif = "/dapin.txt";
       String lvl;
     }
     if (files.exists(pinif)) {
       String pins = files.read(pinif);
       pini = Int.new(pins);
     }
   }

  configState(List cmdl) String {
     String pins = cmdl[3];
     unless (pins.isInteger) {
       return("error: pin must be an integer");
     }
     pini = Int.new(pins);
     files.safeWrite(pinif, pins);
     return("switch pin now " + pins);
   }

   doState(List cmdl) String {
     "in dostate".print();
     String scm = cmdl[2];
     if (scm == setlvll) {
        String inlvl = cmdl[3];
        Int inlvli = app.strToInt(inlvl);
        if (inlvli < 0 || inlvli > 255) {
          inlvli = 255;
        }
        inlvl = inlvli.toString();
        lvl = inlvl;
        inlvl.print();
        files.safeWrite(stf, inlvl);
        /*} else {
          if (inlvli < 0 || inlvli > 255) {
            inlvli = 255;
          } else {
            inlvli = 255 - inlvli;
          }
        }*/
        app.pinModeOutput(pini);
        app.analogWrite(pini, inlvli);
     }
     if (scm == setrlvll) {
     }
     return("ok");
   }
   
   clearStates() {

   }

}
