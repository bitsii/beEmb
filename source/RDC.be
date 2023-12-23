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

class Embedded:ReverseDimmerControl(Embedded:DimmerControl) {

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
        if (wlvli < 0 || wlvli > 255) { wlvli = 255; }
      }
     }
     wlvli = 255 - wlvli; //255-255 = 0, most bright, 255-1=254 least bright
     lastWlvli = wlvli; //avoid gc issues
     app.pinModeOutput(pini);
     app.analogWrite(pini, wlvli);
   }

}
