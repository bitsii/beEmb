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

class Embedded:NodeMcuLeds(Embedded:Lights) {

   buildSwInfo() {
     if (TS.isEmpty(swSpec)) {
       swSpec = "0.NodeMcuLeds.14";
     }
     super.buildSwInfo();
   }

   buildControls() {
     //config ctlconfver.control.ctlconf,args.control.ctlconf,args
     if (TS.isEmpty(controlSpec)) {
       //controlSpec = "";
       //controlSpec = "0.sw.16";  //one sw on 16 - dollatek
       //controlSpec = "0.sw.16.sw.2";  //sw on 16 and 2
       controlSpec = "0.sw.16.dim.2";  //sw on 16 dim on 2 - nodemcu
     }
     super.buildControls();
   }

}
