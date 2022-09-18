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
     minVer = 43;
   }

   loadStates() {
     slots {
       String lvlf = "/dalvl.txt";
       String cmdf = "/dacmd.txt";
       String lvll = "lvl";
       String rlvll = "rlvl";
       //on = 0, off = 255
       String get = "get";
       Int pini = 16; //2
       String pinif = "/dapin.txt";
       Int lvli;
       String lvl;
       String cmd;
     }
     if (files.exists(pinif)) {
       String pins = files.read(pinif);
       pini = Int.new(pins);
     }
     if (files.exists(lvlf)) {
       String inlvl = files.read(lvlf);
     }
     if (files.exists(cmdf)) {
       String incmd = files.read(cmdf);
     }
     if (TS.notEmpty(inlvl) && TS.notEmpty(incmd)) {
       doState(Map.new().put(incmd, inlvl));
     }
   }

   configState(Map cmds) String {
     String pins = cmds["pin"];
     unless (pins.isInteger) {
       return("error: pin must be an integer");
     }
     pini = Int.new(pins);
     files.safeWrite(pinif, pins);
     return("switch pin now " + pins);
   }

   doState(Map cmds) String {
     "in dostate".print();
     String inlvl = cmds[lvll];
     String inrlvl = cmds[rlvll];
     //String inget = cmds["get"];
     if (TS.notEmpty(inlvl)) {
        lvli = app.strToInt(inlvl);
        if (lvli < 0 || lvli > 255) {
          lvli = 255;
        }
        cmd = lvll;
        lvl = inlvl;
        app.delay(1);
        app.pinModeOutput(pini);
        app.analogWrite(pini, lvli);
        files.safeWrite(lvlf, inlvl);
        files.safeWrite(cmdf, lvll);
     } elseIf (TS.notEmpty(inrlvl)) {
        lvli = app.strToInt(inrlvl);
        if (lvli < 0 || lvli > 255) {
          lvli = 255;
        } else {
          lvli = 255 - lvli;
        }
        cmd = rlvll;
        lvl = inrlvl;
        app.pinModeOutput(pini);
        app.analogWrite(pini, lvli);
        files.safeWrite(lvlf, inrlvl);
        files.safeWrite(cmdf, rlvll);
     }
     return("ok");
   }
   
   clearStates() {
     if (files.exists(lvlf)) {
       files.delete(lvlf);
     }
     if (files.exists(cmdf)) {
       files.delete(cmdf);
     }
   }

}
