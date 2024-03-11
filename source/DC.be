/*
 * Copyright (c) 2021-2023, the Brace Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

import Math:Int;
import Text:String;
import Text:Strings as TS;
import Embedded:AppShell;
import Embedded:Config;

import Embedded:CommonNames as CNS;

class Embedded:DimmerControl {

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
       String on = CNS.on;
       String off = CNS.off;
       String setsw = "setsw";
       String getsw = "getsw";
       Int dclvli;
       Int dcswi;
       Int lastWlvli;
     }
     fields {
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

   doWrite() {
     //from app 1 is min 255 is max
     //large numbers bright, small number less bright, 255 most bright

     String wsw = sw;
     String wlvl = lvl;

     if (wsw == off) {
       wlvli = 0;
     } else {
      if (TS.isEmpty(wlvl)) {
        wlvli = 255;
      } else {
        Int wlvli = app.strToInt(wlvl);
        if (wlvli < 1) { wlvli = 1; }
        if (wlvli > 255) { wlvli = 255; }
      }
     }
     if (diri != 0) {
       wlvli = 255 - wlvli; //255-255 = 0, most bright, 255-1=254 least bright
     }
     lastWlvli = wlvli; //avoid gc issues
     app.pinModeOutput(pini);
     app.analogWrite(pini, wlvli);
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
      } elseIf (scm == getlvl) {
        if (TS.notEmpty(lvl)) {
          return(lvl);
        } else {
          return(ud);
        }
      } elseIf (scm == setlvl) {
        String inlvl = cmdl[4];
        sw = on;
        lvl = inlvl;
        config.put(dcswi, sw);
        config.put(dclvli, lvl);
        doWrite();
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     } elseIf (scm == setsw) {
        String insw = cmdl[4];
        if (insw == on) {
          sw = on;
          config.put(dcswi, sw);
          doWrite();
        } elseIf (insw == off) {
          sw = off;
          config.put(dcswi, sw);
          doWrite();
        }
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     }
     return(ok);
   }
   
   clearStates() {
     config.put(dcswi, off);
     config.put(dclvli, "");
   }

}
