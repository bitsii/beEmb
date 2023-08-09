// Copyright 2021 The Bennt Embed Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:Files;
use Embedded:Aes as Crypt;
use Encode:Url as EU;
use Embedded:AppShell;

class Embedded:SwitchAndDimmer(Embedded:AppShell) {

   buildControl(Int conPos, String conName, String conArgs) {
     if (conName == "sw") {
       auto swc = Embedded:SwitchControl.new(self, conPos, conName, conArgs);
       return(swc);
     } elseIf (conName == "dim") {
       auto dimc = Embedded:DimmerControl.new(self, conPos, conName, conArgs);
       return(dimc);
     } else {
       "Unknown control conName in SwitchAndDimmer".print();
     }
     return(null);
   }

}
