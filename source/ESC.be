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

class Embedded:ExclusiveSwitchControl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int swaPos;
       Int swbPos;
       String conType = _conName;
     }
     fields {
       Int lastEvent = Int.new();
     }
     //pini = Int.new(_conArgs);
     if (_conArgs.has(",")) {
        auto cal = _conArgs.split(",");
        swaPos = app.strToInt(cal[0]);
        swbPos = app.strToInt(cal[1]);
     }
   }

   conTypeGet() String {
     return(conType);
   }

   initControl() {
     slots {
       String on = "on";
       String off = "off";
       String setp = "set";
       String setsw = "setsw";
       any swa;
       any swb;
     }
     swa = ash.controls.get(swaPos);
     swb = ash.controls.get(swbPos);
     ash.chkds += self;
   }

   checkDoState(Int ctlPos, List cmdl) {
     String scm = cmdl[3];
     if (scm.begins(setp)) {
       unless (scm == setsw && cmdl[4] == off) {
        if (ctlPos == swaPos) {
          if (swb.sw == on) {
            return(false);
          }
        } elseIf (ctlPos == swbPos) {
          if (swa.sw == on) {
            return(false);
          }
        }
       }
     }
     return(true);
   }

   doState(List cmdl) String {
     return("na");
   }

   clearStates() {

   }
   
}
