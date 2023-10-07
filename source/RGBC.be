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
use Embedded:PWMControl as PWM;

class Embedded:RGBControl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int lastSwEvent = Int.new();
       String conArgs = _conArgs;
       List pwms = List.new(); //rgb red green blue
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
     }
     fields {
       String rgb;
       String sw;
     }
     if (conArgs.has(",")) {
        auto cal = conArgs.split(",");
        for (Int i = 0;i < cal.size;i++=) {
          Int ic = app.strToInt(cal[i]);
          PWM pwm = ash.controls.get(ic);
          pwms += pwm;
        }
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
      return("undefined");
     } elseIf (scm == setrgb) {
        rgb = cmdl[4];
        ("rgb " + rgb).print();
     }
     return("ok");
   }

   clearStates() {

   }
   
}
