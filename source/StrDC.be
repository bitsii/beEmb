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

//strobe controller
//checks sw for "on" or "off"
class Embedded:StrDC {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int dcp;
       Int togglePause = 0;
       Int toggleOn = 0;
       Bool outPause = false;
       Bool inOn = false;
       Int zero = 0;
       Int pauseWin = 1000;
       Int onWin = 100;
       Int dcle;
       Int dclvl = 0;
       Bool dimison = false;
       Int tff = 255;
     }
     fields {
       Int conPos = _conPos;
       Int lastEvent = Int.new();
       String conName = _conName;
     }
     if (_conArgs.has(",")) {
        auto cal = _conArgs.split(",");
        dcp = app.strToInt(cal[0]);
     } else {
        dcp = app.strToInt(_conArgs);
     }
   }

   initControl() {
     slots {
       String on = "on";
       String off = "off";
       Embedded:DimmerControl dc;
     }
     dc = ash.controls.get(dcp);
     ash.loopers += self;
   }

   doState(List cmdl) String {
     return("na");
   }

   clearStates() {

   }

   handleLoop() {
     //in pause every other second
     //when not in pause on/off every 250ms
     if (undef(dc) || undef(dc.sw)) { return(self); }
     if (undef(dcle) || dcle != dc.lastEvent) {
       if (dc.sw == on) {
         dimison = true;
       } else {
         dimison = false;
       }
       if (def(dc.lvl)) {
         dclvl.setValue(app.strToInt(dc.lvl));
       }
       if (undef(dcle)) {
         dcle = Int.new();
       }
       dcle.setValue(dc.lastEvent);
     }
     Int nowup = ash.nowup;
     if (nowup > togglePause) {
       togglePause.setValue(nowup);
       togglePause += pauseWin;
       outPause = outPause.not();
     }
     if (nowup > toggleOn) {
       toggleOn.setValue(nowup);
       toggleOn += onWin;
       inOn = inOn.not();
       Int pini = dc.pini;
       if (dimison && outPause && inOn) {
         //turn it on
         app.pinModeOutput(pini);
         app.analogWrite(pini, dclvl);
       } else {
         //turn it off
         app.pinModeOutput(pini);
         app.analogWrite(pini, tff);
       }
     }
   }
   
}
