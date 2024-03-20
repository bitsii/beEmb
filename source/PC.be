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
use Text:String;
use Text:Strings as TS;
use Embedded:AppShell;
use Embedded:Config;

use Embedded:CommonNames as CNS;

class Embedded:PWMControl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       String conType = _conName;
       Int conPos = _conPos;
       String ok = CNS.ok;
       String ud = CNS.undefined;
       Int diri = 0;
     }
     fields {
       Int lastEvent = Int.new();
       Int pini;
     }
     //pini = Int.new(_conArgs);
     if (_conArgs.contains(",")) {
        var cal = _conArgs.split(",");
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
       String setlvl = "setlvl";
       String getlvl = "getlvl";
       Int dclvli;
       Int lastWlvli;
     }
     fields {
       String lvl;
     }

     dclvli = config.getPos("dc.lvl." + conPos);

    String inlvl = config.get(dclvli);
    if (TS.notEmpty(inlvl)) {
      lvl = inlvl;
      doState(List.new().addValue("dostate").addValue("notpw").addValue(conPos.toString()).addValue(setlvl).addValue(lvl));
    }

   }

   doWrite() {
     //from app 0 is min 255 is max

    String wlvl = lvl;
    if (TS.notEmpty(wlvl)) {
      Int wlvli = app.strToInt(wlvl);
      if (wlvli < 0) { wlvli = 0; }
      if (wlvli > 255) { wlvli = 255; }
      if (diri != 0) {
       wlvli = 255 - wlvli; //255-255 = 0, most bright, 255-1=254 least bright
     }
     lastWlvli = wlvli; //avoid gc issues
     app.pinModeOutput(pini);
     app.analogWrite(pini, wlvli);
    }
   }

   doState(List cmdl) String {
     //"in dostate".print();
     String scm = cmdl[3];
     if (scm == getlvl) {
        if (TS.notEmpty(lvl)) {
          return(lvl);
        } else {
          return(ud);
        }
      } elseIf (scm == setlvl) {
        String inlvl = cmdl[4];
        lvl = inlvl;
        config.put(dclvli, lvl);
        doWrite();
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     }
     return(ok);
   }
   
   clearStates() {
     config.put(dclvli, "");
   }

}
