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
use Encode:Url as EU;
use Embedded:AppShell;

class Embedded:Custom(Embedded:AppShell) {

   buildControl(Int conPos, String conName, String conArgs) {
     if (conName == "cus") {
       var cus = Embedded:CustomControl.new(self, conPos, conName, conArgs);
       return(cus);
     } else {
       "Unknown control conName in Custom".print();
     }
     return(null);
   }

}
