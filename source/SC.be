/*
 * Copyright (c) 2021-2023, the Brace Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:AppShell;
use Embedded:Config;

use Embedded:CommonNames as CNS;

class Embedded:SwitchControl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Int pini;
       Int diri = 0;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int conPos = _conPos;
       String conType = _conName;
       String ok = CNS.ok;
       String ud = CNS.undefined;
     }
     fields {
       Int lastEvent = Int.new();
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

   conTypeGet() String {
     return(conType);
   }

   initControl() {
     slots {
       Int scswi;
       //on = 0, off = 255
       String getsw = "getsw";
       String on = CNS.on;
       String off = CNS.off;
       String setsw = "setsw";
     }
     fields {
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
     //"in dostate".print();
     String scm = cmdl[3];
     if (scm == getsw) {
      if (TS.notEmpty(sw)) {
        return(sw);
        } else {
        return(ud);
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
     return(ok);
   }
   
   clearStates() {
     config.put(scswi, off);
   }

}
