// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;
use Text:String;
use Text:Strings as TS;
use Embedded:AppShell;
use Embedded:Config;

class Embedded:DimmerControl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Int pini;
       Config config = ash.config;
       Embedded:App app = ash.app;
     }
     fields {
       Int conPos = _conPos;
       Int lastEvent = Int.new();
     }
     //pini = Int.new(_conArgs);
     pini = app.strToInt(_conArgs);
   }

   loadStates() {
     slots {
       String setlvll = "setlvl";
       String setrlvll = "setrlvl";
       String getlvl = "getlvl";
       String on = "on";
       String off = "off";
       String setsw = "setsw";
       String getsw = "getsw";
       //on = 0, off = 255
       Int dclvli;
       Int dcswi;
       String lvl;
       String sw;
     }
     dclvli = config.getPos("dc.lvl." + conPos);
     dcswi = config.getPos("dc.sw." + conPos);

     String inlvl = config.get(dclvli);
     if (TS.notEmpty(inlvl)) {
       lvl = inlvl;
     }

     String insw = config.get(dcswi);
     if (TS.notEmpty(insw)) {
       sw = insw;
       doState(List.new().addValue("dostate").addValue("notpw").addValue(conPos.toString()).addValue(setsw).addValue(sw));
     }
   }

   doState(List cmdl) String {
     "in dostate".print();
     String scm = cmdl[3];
     if (scm == getsw) {
       if (TS.notEmpty(sw)) {
         return(sw);
       } else {
        return("undefined");
       }
      } elseIf (scm == getlvl) {
        if (TS.notEmpty(lvl)) {
          return(lvl);
        } else {
          return("undefined");
        }
      } elseIf (scm == setlvll || scm == setrlvll) {
        String inlvl = cmdl[4];
        Int inlvli = app.strToInt(inlvl);
        //Int inlvli = Int.new(inlvl);
        if (scm == setlvll) {
          if (inlvli < 0 || inlvli > 255) {
            inlvli = 255;
          }
        } else {
          if (inlvli < 0 || inlvli > 255) {
            inlvli = 255;
          } else {
            inlvli = 255 - inlvli;//255 - x = y; y + x = 255;255 - y = x
          }
        }
        if (inlvli == 255) { inlvli = 254; }
        //inlvl = inlvli.toString();
        inlvl = app.intToStr(inlvli);
        lvl = inlvl;
        inlvl.print();
        sw = on;
        config.put(dcswi, on);
        config.put(dclvli, inlvl);
        app.pinModeOutput(pini);
        app.analogWrite(pini, inlvli);
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     } elseIf (scm == setsw) {
        String insw = cmdl[4];
        if (insw == on) {
          if (TS.notEmpty(lvl)) {
            inlvli = app.strToInt(lvl);
            //inlvli = Int.new(lvl);
          } else {
            inlvli = 0;
          }
          on.print(); //write crashes without
          app.pinModeOutput(pini);
          app.analogWrite(pini, inlvli);
          sw = insw;
          config.put(dcswi, on);
        } elseIf (insw == off) {
          off.print(); //write crashes without
          app.pinModeOutput(pini);
          app.analogWrite(pini, 255);
          sw = insw;
          config.put(dcswi, off);
        }
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     }
     return("ok");
   }
   
   clearStates() {

   }

}
