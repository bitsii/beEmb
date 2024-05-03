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

class Embedded:SwitchIndicatorControl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Int pini;
       Int diri = 0;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int ic;
       Int lastSwEvent = Int.new();
       Int conPos = _conPos;
       String conType = _conName;
     }
     fields {
       Int lastEvent = Int.new();
     }
     //pini = Int.new(_conArgs);
     if (_conArgs.has(",")) {
        var cal = _conArgs.split(",");
        spin = cal[0];
        diri = app.strToInt(cal[1]);
        ic = app.strToInt(cal[2]);
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
       String on = CNS.on;
       String off = CNS.off;
       any sc;
     }
     fields {
       String sw;
     }
     sc = ash.controls.get(ic);
     ash.loopers += self;
   }

   doState(List cmdl) String {
     return("na");
   }

   clearStates() {

   }

   handleLoop() {
     Int scle = sc.lastEvent;
     if (scle != lastSwEvent) {
       lastSwEvent.setValue(scle);
       String scsw = sc.sw;
       if (TS.notEmpty(scsw)) {
        if (TS.isEmpty(sw) || sw != scsw) {
          doSwitch(scsw);
        }
       }
     }
   }

   doSwitch(String insw) {
     //"in doSwitch".print();
     if (insw == on) {
      on.print(); //write crashes without
      app.pinModeOutput(pini);
      if (diri == 0) {
        app.analogWrite(pini, 0);
      } else {
        app.analogWrite(pini, 255);
      }
      sw = insw;
    } elseIf (insw == off) {
      off.print(); //write crashes without
      app.pinModeOutput(pini);
      if (diri == 0) {
        app.analogWrite(pini, 255);
      } else {
        app.analogWrite(pini, 0);
      }
      sw = insw;
    }
   }
   
}
