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
     devCode = "gdi";
     majVer = 1;
     minVer = 24;
   }

   loadStates() {
     fields {
       String swf = "/dasw.txt";
       String lvlf = "/dalvl.txt";
       //on = 0, off = 255
       String on = "on";
       String off = "off";
       String lvll = "lvl";
       String rlvll = "rlvl";
       String getl = "get";
       String swl = "sw";
       Int pini = 16; //2
       String pinif = "/dapini.txt";
       String sw;
       Int lvl;
     }
     if (files.exists(pinif)) {
       String pins = files.read(pinif);
       pini = Int.new(pins);
     }
     if (files.exists(swf)) {
       String insw = files.read(swf);
     }
     if (files.exists(lvlf)) {
       String inslvl = files.read(lvlf);
     }
     if (TS.isEmpty(insw)) {
       insw = off;
     }
     if (TS.isEmpty(inslvl)) {
       inslvl = "0";
     }
     sw = insw;
     lvl = Int.new(inslvl);
     doState(Map.new().put(swl, insw).put(lvll, inslvl));
   }

   configState(Map cmds) String {
     String pins = cmds["pin"];
     unless (pins.isInteger) {
       return("error: pin must be an integer");
     }
     pini = Int.new(pins);
     writeLater.put(pinif, pins);
     return("switch pin now " + pins);
   }

   doState(Map cmds) String {
     "in dostate".print();
     String inslvl = cmds[lvll];
     String insrlvl = cmds[rlvll];
     String inssw = cmds[swl];
     String insget = cmds[getl];
     if (TS.notEmpty(inssw) && inssw == on) {
        on.print();
        app.pinModeOutput(pini);
        app.analogWrite(pini, lvl);
        sw = inssw;
        writeLater.put(swf, sw);
     } elseIf (TS.notEmpty(inssw) && inssw == off) {
        off.print();
        app.pinModeOutput(pini);
        app.analogWrite(pini, 255);
        sw = inssw;
        writeLater.put(swf, sw);
     }
     if (TS.notEmpty(inslvl) && inslvl.isInteger) {
        Int tmlvl = Int.new(inslvl);
        if (tmlvl > 255 || tmlvl < 0) {
          return("error: invalid level");
        }
        if (sw == on) {
          app.pinModeOutput(pini);
          app.analogWrite(pini, tmlvl);
        }
        lvl = tmlvl;
        writeLater.put(lvlf, lvl.toString());
     } elseIf (TS.notEmpty(insrlvl) && insrlvl.isInteger) {
        tmlvl = Int.new(insrlvl);
        if (tmlvl > 255 || tmlvl < 0) {
          return("error: invalid level");
        }
        tmlvl = 255 - tmlvl;
        if (sw == on) {
          app.pinModeOutput(pini);
          app.analogWrite(pini, tmlvl);
        }
        lvl = tmlvl;
        writeLater.put(lvlf, lvl.toString());
      }
      if (TS.notEmpty(insget) && insget == swl) {
         if (TS.notEmpty(sw)) {
          return(sw);
         } else {
          return("undefined");
         }
       } elseIf (TS.notEmpty(insget) && insget == lvll) {
         if (def(lvl)) {
          return(lvl.toString());
         } else {
          return("undefined");
         }
       }
     return("ok");
   }
   
   clearStates() {
     if (files.exists(swf)) {
       files.delete(swf);
     }
     if (files.exists(lvlf)) {
       files.delete(lvlf);
     }
     sw = null;
     lvl = null;
   }

}
