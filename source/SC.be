// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:AppShell;
use Embedded:Config;

class Embedded:SwitchControl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Int pini;
       Int diri = 0;
       Config config = ash.config;
       Embedded:App app = ash.app;
     }
     fields {
       Int conPos = _conPos;
       Int lastEvent = Int.new();
       String conName = _conName;
     }
     //pini = Int.new(_conArgs);
     if (_conArgs.has(",")) {
        auto cal = _conArgs.split(",");
        spin = cal[0];
        String sdir = cal[1];
        diri = app.strToInt(sdir);
     } else {
      String spin = _conArgs;
     }
     pini = app.strToInt(spin);
   }

   loadStates() {
     slots {
       Int scswi;
       //on = 0, off = 255
       String on = "on";
       String off = "off";
       String getsw = "getsw";
       String setsw = "setsw";
       String sw;
     }
     scswi = config.getPos("sc.sw." + conPos);

     String insw = config.get(scswi);
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
     } elseIf (scm == setsw) {
        String insw = cmdl[4];
        if (insw == on) {
          on.print(); //write crashes without
          app.pinModeOutput(pini);
          if (diri == 0) {
            app.analogWrite(pini, 0);
          } else {
            app.analogWrite(pini, 255);
          }
          sw = insw;
          config.put(scswi, on);
        } elseIf (insw == off) {
          off.print(); //write crashes without
          app.pinModeOutput(pini);
          if (diri == 0) {
            app.analogWrite(pini, 255);
          } else {
            app.analogWrite(pini, 0);
          }
          sw = insw;
          config.put(scswi, off);
        }
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     }
     return("ok");
   }
   
   clearStates() {

   }

}
