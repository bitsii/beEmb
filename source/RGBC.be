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

class Embedded:RGBControl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {

     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int lastSwEvent = Int.new();
       String conArgs = _conArgs;
       Int zero = 0;
       Int twofity = 255;
     }
     fields {
       Int conPos = _conPos;
       Int lastEvent = Int.new();
       String conName = _conName;
     }

   }

   initControl() {
     slots {
       String on = "on";
       String off = "off";
       String getrgb = "getrgb";
       String setrgb = "setrgb";
       String setsw = "setsw";
       String getsw = "getsw";
       Int rp;
       Int gp;
       Int bp;
     }
     fields {
       String rgb;
       String sw;
     }
     if (conArgs.has(",")) {
        auto cal = conArgs.split(",");
        if (cal.size < 3) {
          "not enough pins for rgbc".print();
        }
        rp = app.strToInt(cal[0]);
        gp = app.strToInt(cal[1]);
        bp = app.strToInt(cal[2]);
     }
   }

   doState(List cmdl) String {
     "in dostate rgb".print();
     String scm = cmdl[3];
     if (scm == getsw) {
        if (TS.notEmpty(sw)) {
          return(sw);
        } else {
          return("undefined");
        }
     } elseIf (scm == getrgb) {
      if (TS.notEmpty(rgb)) {
        return(rgb);
      } else {
        return("undefined");
      }
     } elseIf (scm == setrgb) {
        rgb = cmdl[4];
        ("rgb " + rgb).print();
        List rgbl = rgb.split(",");
        Int ri = app.strToInt(rgbl[0]);
        Int gi = app.strToInt(rgbl[1]);
        Int bi = app.strToInt(rgbl[2]);
        if (ri < zero || ri > twofity) {
          ri = zero;
        }
        if (gi < zero || gi > twofity) {
          gi = zero;
        }
        if (bi < zero || bi > twofity) {
          bi = zero;
        }
        app.analogWrite(rp, ri);
        ("rp ri " + rp + " " + ri).print();
        app.analogWrite(gp, gi);
        ("gp gi " + gp + " " + gi).print();
        app.analogWrite(bp, bi);
        ("bp bi " + bp + " " + bi).print();
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     }
     return("ok");
   }

   clearStates() {

   }
   
}
