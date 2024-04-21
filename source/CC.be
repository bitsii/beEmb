/*
 * Copyright (c) 2021-2023, the Beysant Embedded Authors.
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

//copy pfnmsw to pfnmcuex, have a basic pwm led example first, later servo et all
class Embedded:CustomControl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       String conType = _conName;
       Int conPos = _conPos;
       String ok = CNS.ok;
       String ud = CNS.undefined;
     }
     fields {
       Int lastEvent = Int.new();
       String uiConf; //conftype:jsurl:https://theurl could be "na" for not one
       Bool custUi;
     }
     if (_conArgs.has(",")) {
        var cal = _conArgs.split(",");
        uiconf = cal[0];
     } else {
        uiconf = _conArgs;
     }
     if (undef(uiconf) || uiconf == "na") {
       custUi = false;
     } else {
       custUi = true;
     }
   }

   conTypeGet() String {
     return(conType);
   }

   initControl() {
     slots {
       String getuic = "getuic";
       String setstate = "setstate";
       String getstate = "getstate";  //prefer dostatexd to comm state to apps
       Int ccstatei;
       String state;
     }

     ccstatei = config.getPos("cc.state." + conPos);

    String instate = config.get(ccstatei);
    if (TS.notEmpty(instate)) {
      state = instate;
      doState(List.new().addValue("dostate").addValue("notpw").addValue(conPos.toString()).addValue(setstate).addValue(state));
    }

   }

   doState(List cmdl) String {
     //"in dostate".print();
     String scm = cmdl[3];
     if (scm == getstate) {
        if (TS.notEmpty(state)) {
          return(state);
        } else {
          return(ud);
        }
      } elseIf (scm == getuic) {
        if (TS.notEmpty(uiconf)) {
          return(uiconf);
        } else {
          return(ud);
        }
      }
     return(ok);
   }
   
   clearStates() {
     config.put(ccstatei, "");
   }

}
