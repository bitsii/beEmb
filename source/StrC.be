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

//strobe controller
//checks sw for "on" or "off"
class Embedded:StrC {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int rgbp;
       Int togglePause = 0;
       Int toggleOn = 0;
       Bool outPause = false;
       Bool inOn = false;
       Int zero = 0;
       Int pauseWin = 1000;
       Int onWin = 100;
       Int rgble;
       Bool rgbison = false;
       String conType = _conName;
       Int conPos = _conPos;
       String ok = CNS.ok;
       String ud = CNS.undefined;
     }
     fields {
       Int lastEvent = Int.new();
     }
     if (_conArgs.has(",")) {
        var cal = _conArgs.split(",");
        rgbp = app.strToInt(cal[0]);
     } else {
        rgbp = app.strToInt(_conArgs);
     }
   }

   conTypeGet() String {
     return(conType);
   }

   initControl() {
     slots {
       Embedded:RGBControl rgb;
       Int scswi;
       String getsw = "getsw";
       Bool swon = false;
     }
     fields {
       String on = CNS.on;
       String off = CNS.off;
       String setsw = "setsw";
       String sw;
     }
     rgb = ash.controls.get(rgbp);
     ash.loopers += self;

     scswi = config.getPos("sc.sw." + conPos);

     String insw = config.get(scswi);
     if (TS.notEmpty(insw)) {
       sw = insw;
       doState(List.new().addValue("dostate").addValue("notpw").addValue(conPos.toString()).addValue(setsw).addValue(sw));
     }
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
          if (def(rgble) && def(rgb)) {
            if (rgbison) {
              rgbOn();
            } else {
              rgbOff();
            }
          }
        }
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     }
     return(ok);
   }

   rgbOn() {
     Int rp = rgb.rp;
     Int gp = rgb.gp;
     Int bp = rgb.bp;
     Int ri = rgb.ri;
     Int gi = rgb.gi;
     Int bi = rgb.bi;
     if (def(ri) && def(gi) && def(bi)) {
       app.analogWrite(rp, ri);
       app.analogWrite(gp, gi);
       app.analogWrite(bp, bi);
     }
   }

   rgbOff() {
     Int rp = rgb.rp;
     Int gp = rgb.gp;
     Int bp = rgb.bp;
     app.analogWrite(rp, zero);
     app.analogWrite(gp, zero);
     app.analogWrite(bp, zero);
   }

   clearStates() {
     config.put(scswi, off);
   }

   handleLoop() {
     //in pause every other second
     //when not in pause on/off every 250ms
     if (undef(rgb) || undef(rgb.sw)) { return(self); }
     if (undef(rgble) || rgble != rgb.lastEvent) {
       if (rgb.sw == on) {
         rgbison = true;
       } else {
         rgbison = false;
       }
       if (undef(rgble)) {
         rgble = Int.new();
       }
       rgble.setValue(rgb.lastEvent);
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
        if (rgbison && outPause && inOn) {
          //turn it on
          rgbOn();
        } else {
          //turn it off
          rgbOff();
        }
      }
     }
   }
   
}
