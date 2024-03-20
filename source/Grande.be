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
use Embedded:Aes as Crypt;
use Encode:Url as EU;
use Embedded:AppShell;

class Embedded:Grande(Embedded:AppShell) {

   buildControl(Int conPos, String conName, String conArgs) {
     if (conName == "sw") {
       var swc = Embedded:SwitchControl.new(self, conPos, conName, conArgs);
       return(swc);
     } elseIf (conName == "dim" || conName == "gdim") {
       var dimc = Embedded:DimmerControl.new(self, conPos, conName, conArgs);
       return(dimc);
     } elseIf (conName == "pwm") {
       var pwm = Embedded:PWMControl.new(self, conPos, conName, conArgs);
       return(pwm);
     } elseIf (conName == "bu") {
       var buc = Embedded:ButtonControl.new(self, conPos, conName, conArgs);
       return(buc);
     } elseIf (conName == "rgb" || conName == "rgbgdim") {
       var rgb = Embedded:RGBControl.new(self, conPos, conName, conArgs);
       return(rgb);
     } elseIf (conName == "cwgd") {
       var cct = Embedded:CWCtl.new(self, conPos, conName, conArgs);
       return(cct);
     } elseIf (conName == "rgbcwgd" || conName == "rgbcwsgd") {
       var rgbcw = Embedded:RGBCWCtl.new(self, conPos, conName, conArgs);
       return(rgbcw);
     } elseIf (conName == "str") {
       var str = Embedded:StrC.new(self, conPos, "sw", conArgs);
       return(str);
     } else {
       "Unknown control conName in Switch".print();
     }
     return(null);
   }

}
