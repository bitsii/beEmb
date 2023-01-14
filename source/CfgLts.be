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

class Embedded:CfgLts(Embedded:Lights) {

   buildSwInfo() {
     slots {
       Int cgswspeci;
     }
     if (undef(cgswspeci)) {
      cgswspeci = config.getPos("cg.swspec");
     }
     swSpec = config.get(cgswspeci);
     if (TS.isEmpty(swSpec)) {
       swSpec = "0.CfgLts.11";
     }
     super.buildSwInfo();
   }

   buildControls() {
     slots {
       Int cgconpeci;
     }
     if (undef(cgconpeci)) {
      cgconpeci = config.getPos("cg.conspec");
     }
     controlSpec = config.get(cgconpeci);
     //config ctlconfver.control.ctlconf,args.control.ctlconf,args
     if (TS.isEmpty(controlSpec)) {
       controlSpec = "";
     }
     super.buildControls();
   }

}
