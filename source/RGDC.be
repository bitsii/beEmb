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
use Text:String;
use Text:Strings as TS;
use Embedded:AppShell;
use Embedded:Config;

class Embedded:ReverseGammaDimmerControl(Embedded:DimmerControl) {

   gamma(Int start) Int {
     //start^2/255
     //if (true) { return(start); }
     Int res = start.squared;
     res = res / 255;
     if (res < 1) {
       res = 1;
       //log.log("upped gamma to 1");
     }
     if (res > 255) {
       res = 255;
       //log.log("downed gamma to 255");
     }
     //log.log("gamma got " + res + " for " + start);
     return(res);
   }

   doWrite(String wsw, String wlvl) {
     //from app 1 is min 255 is max
     //large numbers less bright, small number more bright, 0 most bright
     //255-1=254, low bright

     if (wsw == off) {
       wlvli = 0;
     } else {
      if (TS.isEmpty(wlvl)) {
        wlvli = 255;
      } else {
        Int wlvli = app.strToInt(wlvl);
        if (wlvli < 1) { wlvli = 1; }
        if (wlvli > 255) { wlvli = 255; }
        wlvli = gamma(wlvli);
      }
     }
     wlvli = 255 - wlvli; //255-255 = 0, most bright, 255-1=254 least bright
     lastWlvli = wlvli; //avoid gc issues
     app.pinModeOutput(pini);
     app.analogWrite(pini, wlvli);
   }

}
