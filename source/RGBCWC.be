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

class Embedded:RGBCWControl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int lastSwEvent = Int.new();
       String conArgs = _conArgs;
       List pwms = List.new(); //rgbcw red green blue cold warm
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
       String getrgbcw = "getrgbcw";
       String setrgbcw = "setrgbcw";
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
     "in dostate rgbcw".print();
     String scm = cmdl[3];
     if (scm == getrgbcw) {
      return("undefined");
     } elseIf (scm == setrgbcw) {
        String evtype = cmdl[4];
        ("evtype " + evtype).print();
        String evmsg = cmdl[5];
        ("evmsg " + evmsg).print();
     }
     return("ok");
   }

   clearStates() {

   }
   
}
