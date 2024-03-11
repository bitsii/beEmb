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

use Embedded:CommonNames as CNS;

class Embedded:ButtonControl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     slots {
       Embedded:AppShell ash = _ash;
       Int pini;
       Int diri = 0; //if 0, on is zero, if this is 1, off is zero
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int onStart = Int.new();
       Int pushTime;
       Int swPos;
       Int resetPushTime;
       Int butVal = Int.new();
       Int lastButVal;
       Int lastTrans;
       Int nextPushTime;
       Int conPos = _conPos;
       String conType = _conName;
       String on = CNS.on;
       String off = CNS.off;
       String setsw = "setsw";
     }
     fields {
       Int lastEvent = Int.new();
     }
     if (_conArgs.has(",")) {
       //all ints comma sep, fields are:
       //0 pin of button
       //1 direction (0, on is 0, 1, off is 0)
       //2 resolution of button (millisecs, only checks button state this often, 2 successive must agree for read)
       //3 switch control position (if is own conPos, ignored)
       //4 min push time to do a device reset, if 0 ignored (millisecs)
        var cal = _conArgs.split(",");
        spin = cal[0];
        diri = app.strToInt(cal[1]);
        pushTime = app.strToInt(cal[2]);
        swPos = app.strToInt(cal[3]);
        resetPushTime = app.strToInt(cal[4]);
     } else {
      String spin = _conArgs;
     }
     pini = app.strToInt(spin);
     onStart--=;
   }

   conTypeGet() String {
     return(conType);
   }

   initControl() {
     app.pinModeInputPullup(pini);
     ash.loopers += self;
   }

   doState(List cmdl) String {
     return("na");
   }
   
   clearStates() {

   }

   handleLoop() {
     Int nowup = ash.nowup;
     if (undef(nextPushTime)) {
       nextPushTime = Int.new();
       nextPushTime.setValue(nowup);
       nextPushTime += pushTime;
       return(self);
     }
     if (nowup > nextPushTime) {
      nextPushTime.setValue(ash.nowup);
      nextPushTime += pushTime;
      app.analogRead(pini, butVal);
      if (undef(lastButVal)) {
        lastButVal = Int.new();
        lastTrans = Int.new();
        lastButVal.setValue(butVal);
        lastTrans.setValue(butVal);
        return(self);
      }
      if (butVal != lastButVal) {
        lastButVal.setValue(butVal);
      } else {
        //same for two reads
        if (butVal != lastTrans) {
            //transition from last two read streak
            lastTrans.setValue(butVal);
            Bool turnedOn = false;
            if (diri == 0 && butVal == 0) {
              turnedOn = true;
            } elseIf (diri == 1 && butVal != 0) {
              turnedOn = true;
            }
            if (turnedOn) {
              onStart.setValue(nowup);
            } elseIf (onStart >= 0) {
              Int ontime = nowup - onStart;
              //("ontime " + ontime).print();
              if (resetPushTime > 0 && ontime > resetPushTime) {
                "reset triggered, resetting".print();
                ash.reset();
              } else {
                "switch toggle triggered".print();
                if (swPos == conPos) {
                  "swPos == conPos, nothing to do".print();
                  return(self);
                }
                dyn swc = ash.controls.get(swPos);
                  if (TS.isEmpty(swc.sw) || swc.sw == off) {
                    swc.doState(List.new().addValue("dostate").addValue("notpw").addValue(swPos.toString()).addValue(setsw).addValue(on));
                  } elseIf (swc.sw == on) {
                    swc.doState(List.new().addValue("dostate").addValue("notpw").addValue(swPos.toString()).addValue(setsw).addValue(off));
                  }
              }
            }
         }
       }
     }
   }

}
