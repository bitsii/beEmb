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

class Embedded:RGBSh(Embedded:AppShell) {

   buildControl(Int conPos, String conName, String conArgs) {
     if (conName == "rgb" || conName == "rgbgdim") {
       var rgb = Embedded:RGBControl.new(self, conPos, conName, conArgs);
       return(rgb);
     } else {
       "Unknown control conName".print();
     }
     return(null);
   }

}
