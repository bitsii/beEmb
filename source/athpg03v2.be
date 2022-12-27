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

class Embedded:Athswa(Embedded:SwitchApp) {

   makeSwInfo() {
     devType = "sw";
     devCode = "athpg03v2";
     majVer = 1;
     minVer = 91;
   }

   loadStates() {
     pini = 12;//Athom 16A US V2 relay 12
     super.loadStates();
   }

}
