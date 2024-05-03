/*
 * Copyright (c) 2021-2023, the Bennt Embedded Authors.
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

class Embedded:CWCtl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {

     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int lastSwEvent = Int.new();
       String conArgs = _conArgs;
       Int zero = 0;
       Int twofity = 255;
       String dfitys = "255,255"; //coldlvl, warmlvl
       String ok = CNS.ok;
       String on = CNS.on;
       String off = CNS.off;
       Int conPos = _conPos;
       String conName = _conName;
     }
     fields {
       Int lastEvent = Int.new();
       String cw = dfitys;
       String sw = off;
     }

   }

   conTypeGet() String {
     return(conName);
   }

   initControl() {
     slots {
       String getcw = "getcw";
       String setcw = "setcw";
       String setsw = "setsw";
       String getsw = "getsw";
       Int cwcwi;
       Int cwswi;
     }
     fields {
       Int cp;
       Int wp;
       Int ci;
       Int wi;
     }

     cwcwi = config.getPos("cws.cw." + conPos);
     cwswi = config.getPos("cws.sw." + conPos);

     if (conArgs.has(",")) {
        var cal = conArgs.split(",");
        if (cal.length < 2) {
          "not enough pins for cws".print();
        }
        cp = app.strToInt(cal[0]);
        wp = app.strToInt(cal[1]);
     }

    String incw = config.get(cwcwi);
    if (TS.notEmpty(incw)) {
      cw = incw;
    }

    String insw = config.get(cwswi);
    if (TS.notEmpty(insw)) {
      sw = insw;
      doState(List.new().addValue("dostate").addValue("notpw").addValue(conPos.toString()).addValue(setsw).addValue(sw));
    }

   }

   doState(List cmdl) String {
     "in dostate rgb".print();
     String scm = cmdl[3];
     if (scm == getsw) {
       return(sw);
     } elseIf (scm == getcw) {
       return(cw);
     } elseIf (scm == setsw) {
        String insw = cmdl[4];
        if (insw == on) {
          //check and off other control if present
          sw = insw;
          config.put(cwswi, on);
          //lastevent et all handled below in common with setrgb
        } elseIf (insw == off) {
          sw = insw;
          config.put(cwswi, off);
          app.analogWrite(cp, zero);
          app.analogWrite(wp, zero);
          "offed wrote zeros".print();
          lastEvent.setValue(ash.nowup);
          ash.lastEventsRes = null;
          return(ok);
        }
     } elseIf (scm == setcw) {
        //check and off other control if present
        sw = on;
        cw = cmdl[4];
        config.put(cwswi, on);
        config.put(cwcwi, cw);
     } else {
       return(ok);
     }
      ("cw " + cw).print();
      List cwl = cw.split(",");
      ci = app.strToInt(cwl[0]);
      wi = app.strToInt(cwl[1]);
      if (ci < zero || ci > twofity) {
        ci = zero;
      }
      if (wi < zero || wi > twofity) {
        wi = zero;
      }
      app.analogWrite(cp, ci);
      app.analogWrite(wp, wi);
      lastEvent.setValue(ash.nowup);
      ash.lastEventsRes = null;
      return(ok);
   }

   clearStates() {
     config.put(cwswi, off);
     config.put(cwcwi, dfitys);
   }
   
}
