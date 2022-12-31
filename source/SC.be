// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:Files;
use Embedded:Aes as Crypt;
use Encode:Url as EU;
use Embedded:AppShell;
use Embedded:Config;

class Embedded:SwitchControl {

   //pinposes //16, 2 nodemcu - Athom 16A US 13 LED 14 RELAY, SONOFF BASIC R2 13 LED 12 RELAY, 16 for dollatek 8285

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
       Int scswi;
       //on = 0, off = 255
       String on = "on";
       String off = "off";
       String getsw = "getsw";
       String setsw = "setsw";
       String sw;
     }
     scswi = config.getPos("sc.sw" + conPos);

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
          app.analogWrite(pini, 0);
          sw = insw;
          config.put(scswi, on);
        } elseIf (insw == off) {
          off.print(); //write crashes without
          app.pinModeOutput(pini);
          app.analogWrite(pini, 255);
          sw = insw;
          config.put(scswi, off);
        }
     }
     return("ok");
   }
   
   clearStates() {

   }

}
