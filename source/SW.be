/*
 * Copyright (c) 2021-2023, the Bennt Embedded Authors.
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

class Embedded:Switch(Embedded:AppShell) {

   buildControl(Int conPos, String conName, String conArgs) {
     if (conName == "sw") {
       var swc = Embedded:SwitchControl.new(self, conPos, conName, conArgs);
       return(swc);
     } else {
       "Unknown control conName in Switch".print();
     }
     return(null);
   }

}
