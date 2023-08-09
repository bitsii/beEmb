// Copyright 2021 The Bennt Embed Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:AppShell;
use Embedded:Config;

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
        diri = app.strToInt(cal[1]);
        ic = app.strToInt(cal[2]);
     } else {
      String spin = _conArgs;
     }
     pini = app.strToInt(spin);
   }

   initControl() {
     slots {
       String on = "on";
       String off = "off";
       Embedded:SwitchControl sc;
     }
     fields {
       String sw;
     }
     sc = ash.controls.get(ic);
     ash.loopers += self;
   }

   doStateMq(String topic, String payload) String {
     return("na");
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
     "in doSwitch".print();
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
