// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:Files;
use Encode:Hex as Hex;
use Embedded:Aes as Crypt;
use Encode:Url as EU;
use Embedded:AppShell;

class Embedded:LightApp(AppShell) {

   makeSwInfo() {
     devType = "light";
     majVer = 1;
     minVer = 1;
   }

   loadStates() {
     fields {
       String statesf = "/latstates.txt";
       //on = 0, off = 255
       String on = "on";
       String off = "off";
       String get = "get";
       Int pini = 16; //2
       String lastSavedState;
       String lastState;
     }
     if (files.exists(statesf)) {
       lastSavedState = files.read(statesf);
       lastState = lastSavedState;
       doState(lastSavedState);
     }
   }

   doState(String state) String {
     "in dostate".print();
     if (TS.notEmpty(state)) {
       //"state".print();
       //state.print();
       if (state == on) {
         on.print();
         app.pinModeOutput(pini);
         app.analogWrite(pini, 0);
         lastState = state;
       } elseIf (state == off) {
         off.print();
         app.pinModeOutput(pini);
         app.analogWrite(pini, 255);
         lastState = state;
       } elseIf (state == get) {
         if (TS.notEmpty(lastState)) {
          return(lastState);
         } else {
          return("undefined");
         }
       }

     }
     return(state);
   }
   
   clearStates() {
     if (files.exists(statesf)) {
       files.delete(statesf);
     }
     lastState = null;
     lastSavedState = null;
   }
   
   saveStates() {
     if (TS.notEmpty(lastState)) {
      if (TS.isEmpty(lastSavedState) || lastState != lastSavedState) {
        "saving state".print();
        Files.write(statesf, lastState);
        lastSavedState = lastState;
      }
     }
   }

}
