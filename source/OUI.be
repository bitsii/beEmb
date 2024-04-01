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

class Embedded:Oui(Embedded:AppShell) {

   buildControl(Int conPos, String conName, String conArgs) {
     if (conName == "twcc") {
       var twcc = Embedded:Twcc.new(self, conPos, conName, conArgs);
       return(twcc);
     } else {
       "Unknown control conName in Oui".print();
     }
     return(null);
   }

}
