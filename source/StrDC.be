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
       String conType = "sw";
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

   conTypeGet() String {
     return(conType);
   }

   initControl() {
     slots {
       Embedded:DimmerControl dc;
       Int scswi;
       String getsw = "getsw";
       Bool swon = false;
     }
     fields {
       String on = "on";
       String off = "off";
       String setsw = "setsw";
       String sw;
     }
     dc = ash.controls.get(dcp);
     ash.loopers += self;

     scswi = config.getPos("sc.sw." + conPos);

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
          sw = insw;
          config.put(scswi, on);
          swon = true;
        } elseIf (insw == off) {
          sw = insw;
          config.put(scswi, off);
          swon = false;
          if (def(dcle) && def(dc) && def(dc.pini)) {
            Int pini = dc.pini;
            if (dimison) {
              app.pinModeOutput(pini);
              app.analogWrite(pini, dclvl);
            } else {
              app.pinModeOutput(pini);
              app.analogWrite(pini, tff);
            }
          }
        }
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     }
     return("ok");
   }

   clearStates() {
     config.put(scswi, off);
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
     if (swon) {
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
   
}
