// Copyright 2021 The BraceEmb Authors. All rights reserved.
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

class Embedded:TinyWeb { }
class Embedded:SerServer { }

class Embedded:AthomPlugV2(Embedded:AppShell) {

   buildControl(Int conPos, String conName, String conArgs) {
     if (conName == "sw") {
       auto swc = Embedded:SwitchControl.new(self, conPos, conName, conArgs);
       return(swc);
     } else {
       "Unknown control conName in Switch".print();
     }
     return(null);
   }

   buildSwInfo() {
     if (TS.isEmpty(swSpec)) {
       swSpec = "0.AthomPlugV2.21";
     }
     super.buildSwInfo();
   }

   buildControls() {
     //config ctlconfver.control.ctlconf,args.control.ctlconf,args
     //todo physical button toggles, led solid if on wifi, blink if station
     //physical button a control, args say what to toggle (pos), led is a control, controls get events - state, tick
     if (TS.isEmpty(controlSpec)) {
       controlSpec = "0.sw.12,1";  //12 is switch (rev), 13 is led - athom plug v2 us - esp8266ex 2mb
       //controlSpec = "0.sw.16,1";  //one sw on 16 - dollatek
     }
     super.buildControls();
   }

}
