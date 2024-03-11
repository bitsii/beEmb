/*
 * Copyright (c) 2021-2023, the Brace Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

import Math:Int;
import Embedded:Wifi;
import Text:String;
import Text:Strings as TS;
import Embedded:Aes as Crypt;
import Encode:Url as EU;
import Embedded:AppShell;

class Embedded:Grande(Embedded:AppShell) {

   buildControl(Int conPos, String conName, String conArgs) {
     if (conName == "sw") {
       var swc = Embedded:SwitchControl.new(self, conPos, conName, conArgs);
       return(swc);
     } elseIf (conName == "dim" || conName == "gdim") {
       var dimc = Embedded:DimmerControl.new(self, conPos, conName, conArgs);
       return(dimc);
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
