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

class Embedded:PWMControl {

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
       String conName = _conName;
     }
     //pini = Int.new(_conArgs);
     if (_conArgs.has(",")) {
        auto cal = _conArgs.split(",");
        spin = cal[0];
        String dsv = cal[1];
        Int dsvi = app.strToInt(dsv);
     } else {
      String spin = _conArgs;
     }
     pini = app.strToInt(spin);
   }

   initControl() {
     slots {
       String setlvll = "setlvl";
       String setrlvll = "setrlvl";
       String getlvl = "getlvl";
       Int lmax = 255;
       Int dclvli;
     }
     fields {
       String lvl;
     }

   }

   doStateMq(String topic, String payload) String {
     ("in doStateMq dc " + topic + " " + payload).print();
     return(null);
   }

   doState(List cmdl) String {
     "in dostate".print();
     String scm = cmdl[3];
     if (scm == getlvl) {
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
          if (inlvli < 0 || inlvli > lmax) {
            inlvli = lmax;
          }
        } else {
          if (inlvli < 0 || inlvli > lmax) {
            inlvli = lmax;
          } else {
            inlvli = lmax - inlvli;//lmax - x = y; y + x = lmax;lmax - y = x
          }
        }
        //inlvl = inlvli.toString();
        inlvl = app.intToStr(inlvli);
        lvl = inlvl;
        inlvl.print();
        app.analogWrite(pini, inlvli);
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     }
     return("ok");
   }
   
   clearStates() {
   }

}
