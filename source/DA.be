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

class Embedded:DimmerApp(AppShell) {

   makeSwInfo() {
     devType = "dimmer";
     devCode = "gdi";
     majVer = 1;
     minVer = 41;
   }

   loadStates() {
     slots {
       String lvlf = "/dalvl.txt";
       String rlvlf = "/darlvl.txt";
       //on = 0, off = 255
       String get = "get";
       Int pini = 16; //2
       String pinif = "/dapin.txt";
       Int lvli;
     }
     if (files.exists(pinif)) {
       String pins = files.read(pinif);
       pini = Int.new(pins);
     }
     if (files.exists(lvlf)) {
       String inlvl = files.read(lvlf);
       doState(Map.new().put("lvl", inlvl));
     } elseIf (files.exists(rlvlf)) {
       String inrlvl = files.read(rlvlf);
       doState(Map.new().put("rlvl", inrlvl));
     }
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
     String inlvl = cmds["lvl"];
     String inrlvl = cmds["rlvl"];
     //String inget = cmds["get"];
     if (TS.notEmpty(inlvl)) {
        lvli = app.strToInt(inlvl);
        if (lvli < 0 || lvli > 255) {
          lvli = 255;
        }
        app.pinModeOutput(pini);
        app.analogWrite(pini, lvli);
        writeLater.put(lvlf, inlvl);
        deleteLater.put(rlvlf);
     } elseIf (TS.notEmpty(inrlvl)) {
        lvli = app.strToInt(inrlvl);
        if (lvli < 0 || lvli > 255) {
          lvli = 255;
        } else {
          lvli = 255 - lvli;
        }
        app.pinModeOutput(pini);
        app.analogWrite(pini, lvli);
        writeLater.put(rlvlf, inrlvl);
        deleteLater.put(lvlf);
     }
     return("ok");
   }
   
   clearStates() {
     if (files.exists(lvlf)) {
       files.delete(lvlf);
     }
     if (files.exists(rlvlf)) {
       files.delete(rlvlf);
     }
   }

}
