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
use Embedded:Files;
use Embedded:Aes as Crypt;
use Encode:Url as EU;
use Embedded:AppShell;

class Embedded:RGBL(Embedded:AppShell) {

   buildControl(Int conPos, String conName, String conArgs) {
     if (conName == "pwm" || conName == "pwmh") {
       auto swc = Embedded:PWMControl.new(self, conPos, conName, conArgs);
       return(swc);
     } elseIf (conName == "rgbcw") {
       auto rgbcw = Embedded:RGBCWControl.new(self, conPos, conName, conArgs);
       return(rgbcw);
     } else {
       "Unknown control conName".print();
     }
     return(null);
   }

}
