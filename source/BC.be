// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

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
       Int diri = 0;
       Config config = ash.config;
       Embedded:App app = ash.app;
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
        auto cal = _conArgs.split(",");
        spin = cal[0];
        String sdir = cal[1];
        diri = app.strToInt(sdir);
     } else {
      String spin = _conArgs;
     }
     pini = app.strToInt(spin);
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
     }
   }

}
