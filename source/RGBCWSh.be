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
use Encode:Url as EU;
use Embedded:AppShell;

class Embedded:RGBCWSh(Embedded:AppShell) {

   buildControl(Int conPos, String conName, String conArgs) {
     if (conName == "rgbcwgd" || conName == "rgbcwsgd") {
       var rgbcw = Embedded:RGBCWCtl.new(self, conPos, conName, conArgs);
       return(rgbcw);
     } else {
       "Unknown control conName".print();
     }
     return(null);
   }

}
