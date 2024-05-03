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
use Text:String;
use Text:Strings as TS;
use Embedded:AppShell;
use Embedded:Config;

use Embedded:CommonNames as CNS;

//two wheel car control
class Embedded:Twcc {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       String conName = _conName;
       String conType = "oui";
       Int conPos = _conPos;
       String ok = CNS.ok;
       String ud = CNS.undefined;
     }
     fields {
       Int lastEvent = Int.new();
     }
   }

   conTypeGet() String {
     return(conType);
   }

   initControl() {
     slots {
       String getoif = "getoif";
     }
     fields {
       String oif;
     }
     oif = "1,move,pup,http://192.168.1.184:8080/twc/carcon.html";
   }

   doState(List cmdl) String {
     //"in dostate".print();
     String scm = cmdl[3];
     if (scm == getoif) {
       if (TS.notEmpty(oif)) {
         return(oif);
       } else {
         return(ud);
       }
     }
     return(ok);
   }
   
   clearStates() {
   }

}
