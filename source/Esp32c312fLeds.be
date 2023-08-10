/*
 * Copyright (c) 2021-2023, the Bennt Embed Authors.
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

class Embedded:Esp32c312fLeds(Embedded:Lights) {

   buildSwInfo() {
     if (TS.isEmpty(swSpec)) {
       swSpec = "0.Esp32c312f.10";
     }
     super.buildSwInfo();
   }

   buildControls() {
     //config ctlconfver.control.ctlconf,args.control.ctlconf,args
     if (TS.isEmpty(controlSpec)) {
       //controlSpec = "";
       //controlSpec = "0.sw.16";  //one sw on 16
       //controlSpec = "0.sw.16.sw.2";  //sw on 16 and 2
       controlSpec = "0.sw.2";  //sw on 16 dim on 2
     }
     super.buildControls();
   }

}
