/*
 * Copyright (c) 2021-2023, the Brace Embedded Authors.
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
use Embedded:AppShell;
use Embedded:Config;

class Embedded:RGBGamDimCon(Embedded:RGBControl) {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     super.new(_ash, _conPos, _conName, _conArgs);
     conType = "rgbdim";
   }

   initControl() {
     slots {
       String setlvll = "setlvl";
       String getlvl = "getlvl";
       Int dclvli;
       Int lastWlvli;
       String ud = "undefined";
       Int tff = twofity;
       Int one = 1;
       Int hunk = 100000;
     }
     fields {
       String lvl;
     }

     dclvli = config.getPos("rgbdim.lvl." + conPos);

     String inlvl = config.get(dclvli);
     if (TS.notEmpty(inlvl)) {
       lvl = inlvl;
     }

     super.initControl();
   }

   doWrite() {
     if (sw == off) {
      app.analogWrite(rp, zero);
      app.analogWrite(gp, zero);
      app.analogWrite(bp, zero);
      "offed wrote zeros".print();
     } else {
      ("rgb " + rgb).print();
      List rgbl = rgb.split(",");
      ri = app.strToInt(rgbl[0]);
      gi = app.strToInt(rgbl[1]);
      bi = app.strToInt(rgbl[2]);
      if (ri < zero || ri > twofity) {
        ri = zero;
      }
      if (gi < zero || gi > twofity) {
        gi = zero;
      }
      if (bi < zero || bi > twofity) {
        bi = zero;
      }




      app.analogWrite(rp, ri);
      //("rp ri " + rp + " " + ri).print();
      app.analogWrite(gp, gi);
      //("gp gi " + gp + " " + gi).print();
      app.analogWrite(bp, bi);
      //("bp bi " + bp + " " + bi).print();
     }
   }

   doState(List cmdl) String {
     //"in dostate rgb".print();
     String scm = cmdl[3];
     if (scm == getlvl) {
       if (TS.notEmpty(lvl)) {
         return(lvl);
       } else {
         return(ud);
       }
     } elseIf (scm == setlvll) {
       String inlvl = cmdl[4];
       sw = on;
       lvl = inlvl;
       config.put(rgbswi, sw);
       config.put(dclvli, lvl);
       //doWrite();
       lastEvent.setValue(ash.nowup);
       ash.lastEventsRes = null;
       return(ok);
     }
     return(super.doState(cmdl));
   }

   clearStates() {
     config.put(dclvli, "");
     super.clearStates();
   }
   
}
