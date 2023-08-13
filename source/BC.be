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
     }
     fields {
       Int conPos = _conPos;
       Int lastEvent = Int.new();
       String conName = _conName;
       Int butVal = Int.new();
       Int lastButVal = Int.new();
       Int lastTrans = Int.new();
     }
     if (_conArgs.has(",")) {
       //all ints comma sep, fields are:
       //0 pin of button
       //1 direction (0, on is 0, 1, off is 0)
       //2 min push time to toggle a switch (0 disables) (millisecs)
       //3 switch control position (if field 2 is 0, ignored)
       //4 min push time to do a device reset, if 0 ignored (millisecs)
        auto cal = _conArgs.split(",");
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

   initControl() {
     app.pinModeInputPullup(pini);
     ash.loopers += self;
   }

   doStateMq(String topic, String payload) String {
     return("na");
   }

   doState(List cmdl) String {
     return("na");
   }
   
   clearStates() {

   }

   handleLoop() {
     app.analogRead(pini, butVal);
     if (butVal != lastButVal) {
       lastButVal.setValue(butVal);
       "butVal changed".print();
       butVal.print();
       Bool turnedOn = false;
       if (diri == 0 && butVal == 0) {
         turnedOn = true;
       } elseIf (diri == 1 && butVal != 0) {
         turnedOn = true;
       }
       if (turnedOn) {
         onStart.setValue(ash.nowup);
       } elseIf (onStart >= 0) {
         Int ontime = ash.nowup - onStart;
         ("ontime " + ontime).print();
         if (resetPushTime > 0 && ontime > resetPushTime) {
           "reset triggered, resetting".print();
           ash.reset();
         } elseIf (pushTime > 0 && ontime > pushTime) {
           "switch toggle triggered".print();
           Embedded:SwitchControl swc = ash.controls.get(swPos);
            if (TS.isEmpty(swc.sw) || swc.sw == swc.off) {
              swc.doState(List.new().addValue("dostate").addValue("notpw").addValue(swc.conPos.toString()).addValue(swc.setsw).addValue(swc.on));
            } elseIf (swc.sw == swc.on) {
              swc.doState(List.new().addValue("dostate").addValue("notpw").addValue(swc.conPos.toString()).addValue(swc.setsw).addValue(swc.off));
            }
         }
       }
     }
   }

}
