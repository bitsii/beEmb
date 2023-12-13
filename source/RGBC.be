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
       String twofitys = "255,255,255";
       String ok = "ok";
       String on = "on";
       String off = "off";
       /*Int rmq = twofity;
       Int gmq = twofity;
       Int bmq = twofity;
       Int lvlmq = twofity;*/
     }
     fields {
       Int conPos = _conPos;
       Int lastEvent = Int.new();
       String conName = _conName;
       String rgb = twofitys;
       String sw = off;
     }

   }

   conTypeGet() String {
     return(conName);
   }

   initControl() {
     slots {
       String brightness = "brightness";
       String color = "color";
       String ON = "ON";
       String OFF = "OFF";
       String getrgb = "getrgb";
       String setrgb = "setrgb";
       String setsw = "setsw";
       String getsw = "getsw";
       Int rp;
       Int gp;
       Int bp;
       Int rgbrgbi;
       Int rgbswi;
     }

     rgbrgbi = config.getPos("rgb.rgb." + conPos);
     rgbswi = config.getPos("rgb.sw." + conPos);

     if (conArgs.has(",")) {
        auto cal = conArgs.split(",");
        if (cal.size < 3) {
          "not enough pins for rgbc".print();
        }
        rp = app.strToInt(cal[0]);
        gp = app.strToInt(cal[1]);
        bp = app.strToInt(cal[2]);
     }

    String inrgb = config.get(rgbrgbi);
    if (TS.notEmpty(inrgb)) {
      rgb = inrgb;
    }

    String insw = config.get(rgbswi);
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
     } elseIf (scm == getrgb) {
       return(rgb);
     } elseIf (scm == setsw) {
        String insw = cmdl[4];
        if (insw == on) {
          //check and off other control if present
          sw = insw;
          config.put(rgbswi, on);
          //lastevent et all handled below in common with setrgb
        } elseIf (insw == off) {
          sw = insw;
          config.put(rgbswi, off);
          app.analogWrite(rp, zero);
          app.analogWrite(gp, zero);
          app.analogWrite(bp, zero);
          "offed wrote zeros".print();
          lastEvent.setValue(ash.nowup);
          ash.lastEventsRes = null;
          return(ok);
        }
     } elseIf (scm == setrgb) {
        //check and off other control if present
        sw = on;
        rgb = cmdl[4];
        config.put(rgbswi, on);
        config.put(rgbrgbi, rgb);
     } else {
       return(ok);
     }
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
      //("rp ri " + rp + " " + ri).print();
      app.analogWrite(gp, gi);
      //("gp gi " + gp + " " + gi).print();
      app.analogWrite(bp, bi);
      //("bp bi " + bp + " " + bi).print();
      lastEvent.setValue(ash.nowup);
      ash.lastEventsRes = null;
      return(ok);
   }

   clearStates() {
     config.put(rgbswi, off);
     config.put(rgbrgbi, twofitys);
   }
   
}
