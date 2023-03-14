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

class Embedded:Switch(Embedded:AppShell) {

   //pinposes //16, 2 nodemcu - Athom 16A US 13 LED 14 RELAY, SONOFF BASIC R2 13 LED 12 RELAY, 16 for dollatek 8285

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
       swSpec = "0.Switch.15";
     }
     super.buildSwInfo();
   }

   buildControls() {
     //config ctlconfver.control.ctlconf,args.control.ctlconf,args
     if (TS.isEmpty(controlSpec)) {
       //controlSpec = "";
       //controlSpec = "0.sw.12.sw.13";  //12 is switch, 13 is led - athom plug v2 us - esp8266ex 2mb
       controlSpec = "0.sw.16";  //one sw on 16 - dollatek
       //controlSpec = "0.sw.16.sw.2";  //sw on 16 and 2 - nodemcu
     }
     super.buildControls();
   }

}
