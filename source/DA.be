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

class Embedded:DimmerApp(AppShell) {
   
   makeSwInfo() {
     devType = "dimmer";
     majVer = 1;
     minVer = 2;
   }

   loadStates() {
     fields {
       String swf = "/dasw.txt";
       String lvlf = "/dalvl.txt";
       //on = 0, off = 255
       String on = "on";
       String off = "off";
       String lvlbg = "lvl:";
       String rlvlbg = "rlvl:";
       String getsw = "getsw";
       String getlvl = "getlvl";
       Int pini = 16; //2
       String lastSavedSw;
       String lastSw;
       String lastSavedLvl;
       String lastLvl;
     }
     if (files.exists(swf)) {
       lastSavedSw = files.read(swf);
       lastSw = lastSavedSw;
     }
     if (files.exists(lvlf)) {
       lastSavedLvl = files.read(lvlf);
       lastLvl = lastSavedLvl;
     }
     if (TS.isEmpty(lastSw)) {
       lastSw = off;
     }
     if (TS.isEmpty(lastLvl)) {
       lastLvl = "lvl:0";
     }
     if (lastSw == off) {
       doState(off);
     } else {
       doState(lastLvl);
     }
   }

   doState(String state) String {
     "in dostate".print();
     if (TS.notEmpty(state)) {
       //"state".print();
       //state.print();
       if (state == on) {
         on.print();
         sl = lastLvl.split(":");
         tmlvl = Int.new(sl[1]);
         if (lastLvl.begins(rlvlbg)) {
            tmlvl = 255 - tmlvl;
          }
         app.pinModeOutput(pini);
         app.analogWrite(pini, tmlvl);
         lastSw = state;
       } elseIf (state == off) {
         off.print();
         app.pinModeOutput(pini);
         app.analogWrite(pini, 255);
         lastSw = state;
       } elseIf (state.begins(lvlbg) || state.begins(rlvlbg)) {
         auto sl = state.split(":");
         if (sl.size == 2 && sl[1].isInteger) {
          auto tmlvl = Int.new(sl[1]);
          if (tmlvl > 255 || tmlvl < 0) {
            return("invalid level");
          }
          if (state.begins(rlvlbg)) {
            tmlvl = 255 - tmlvl;
          }
          app.pinModeOutput(pini);
          app.analogWrite(pini, tmlvl);
          lastLvl = state;
          lastSw = on;
         }
       } elseIf (state == getsw) {
         if (TS.notEmpty(lastSw)) {
          return(lastSw);
         } else {
          return("undefined");
         }
       } elseIf (state == getlvl) {
         if (TS.notEmpty(lastLvl)) {
          return(lastLvl);
         } else {
          return("undefined");
         }
       }

     }
     return(state);
   }
   
   clearStates() {
     if (files.exists(swf)) {
       files.delete(swf);
     }
     if (files.exists(lvlf)) {
       files.delete(lvlf);
     }
     lastSw = null;
     lastSavedSw = null;
     lastLvl = null;
     lastSavedLvl = null;
   }
   
   saveStates() {
     if (TS.notEmpty(lastSw)) {
      if (TS.isEmpty(lastSavedSw) || lastSw != lastSavedSw) {
        "saving sw".print();
        Files.write(swf, lastSw);
        lastSavedSw = lastSw;
      }
     }
     if (TS.notEmpty(lastLvl)) {
      if (TS.isEmpty(lastSavedLvl) || lastLvl != lastSavedLvl) {
        "saving lvl".print();
        Files.write(lvlf, lastLvl);
        lastSavedLvl = lastLvl;
      }
     }
   }

}
