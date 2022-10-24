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
     minVer = 70;
   }

   loadStates() {
     slots {
       String setlvll = "setlvl";
       String setrlvll = "setrlvl";
       String on = "on";
       String off = "off";
       String setsw = "setsw";
       //on = 0, off = 255
       Int pini = 16; //2
       Int dalvli;
       Int dapini;
       Int daswi;
       String lvl;
       String sw;
     }
     dalvli = config.getPos("da.lvl");
     dapini = config.getPos("da.pin");
     daswi = config.getPos("da.sw");

     String pins = config.get(dapini);
     if (TS.notEmpty(pins) && pins.isInteger) {
       pini = Int.new(pins);
       ("loaded pin " + pins).print();
     }

     String inlvl = config.get(dalvli);
     if (TS.notEmpty(inlvl)) {
       lvl = inlvl;
     }

     String insw = config.get(daswi);
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
     config.put(dapini, pins);
     pini = Int.new(pins);
     return("dimmer pin now " + pins);
   }

   doState(List cmdl) String {
     "in dostate".print();
     String scm = cmdl[2];
     if (scm == setlvll || scm == setrlvll) {
        String inlvl = cmdl[3];
        Int inlvli = app.strToInt(inlvl);
        if (scm == setlvll) {
          if (inlvli < 0 || inlvli > 255) {
            inlvli = 255;
          }
        } else {
          if (inlvli < 0 || inlvli > 255) {
            inlvli = 255;
          } else {
            inlvli = 255 - inlvli;
          }
        }
        if (inlvli == 255) { inlvli = 254; }
        inlvl = inlvli.toString();
        lvl = inlvl;
        inlvl.print();
        sw = on;
        config.put(daswi, on);
        config.put(dalvli, inlvl);
        app.pinModeOutput(pini);
        app.analogWrite(pini, inlvli);
     } elseIf (scm == setsw) {
        String insw = cmdl[3];
        if (insw == on) {
          if (TS.notEmpty(lvl)) {
            inlvli = app.strToInt(lvl);
          } else {
            inlvli = 0;
          }
          on.print(); //write crashes without
          app.pinModeOutput(pini);
          app.analogWrite(pini, inlvli);
          sw = insw;
          config.put(daswi, on);
        } elseIf (insw == off) {
          off.print(); //write crashes without
          app.pinModeOutput(pini);
          app.analogWrite(pini, 255);
          sw = insw;
          config.put(daswi, off);
        }
     }
     return("ok");
   }
   
   clearStates() {

   }

}
