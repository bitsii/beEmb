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
       Int conPos = _conPos;
       Int pini;
       Config config = ash.config;
       Embedded:App app = ash.app;
     }
     pini = Int.new(_conArgs);
   }

   loadStates() {
     slots {
       String setlvll = "setlvl";
       String setrlvll = "setrlvl";
       String on = "on";
       String off = "off";
       String setsw = "setsw";
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
     if (scm == setlvll || scm == setrlvll) {
        String inlvl = cmdl[4];
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
        config.put(dcswi, on);
        config.put(dclvli, inlvl);
        app.pinModeOutput(pini);
        app.analogWrite(pini, inlvli);
     } elseIf (scm == setsw) {
        String insw = cmdl[4];
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
          config.put(dcswi, on);
        } elseIf (insw == off) {
          off.print(); //write crashes without
          app.pinModeOutput(pini);
          app.analogWrite(pini, 255);
          sw = insw;
          config.put(dcswi, off);
        }
     }
     return("ok");
   }
   
   clearStates() {

   }

}