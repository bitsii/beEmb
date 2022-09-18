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

class Embedded:SwitchApp(AppShell) {

   makeSwInfo() {
     devType = "switch";
     devCode = "gsw";
     majVer = 1;
     minVer = 41;
   }

   loadStates() {
     slots {
       String swf = "/lasw.txt";
       //on = 0, off = 255
       String on = "on";
       String off = "off";
       String get = "get";
       Int pini = 16; //2
       String pinif = "/lapin.txt";
       String sw;
     }
     if (files.exists(pinif)) {
       String pins = files.read(pinif);
       pini = Int.new(pins);
     }
     if (files.exists(swf)) {
       String insw = files.read(swf);
       sw = insw;
       doState(Map.new().put("sw", insw));
     }
   }

   configState(Map cmds) String {
     String pins = cmds["pin"];
     unless (pins.isInteger) {
       return("error: pin must be an integer");
     }
     pini = Int.new(pins);
     files.write(pinif, pins);
     return("switch pin now " + pins);
   }

   doState(Map cmds) String {
     "in dostate".print();
     String insw = cmds["sw"];
     String inget = cmds["get"];
     if (TS.notEmpty(inget)) {
      if (TS.notEmpty(sw)) {
        return(sw);
        } else {
        return("undefined");
        }
     } elseIf (TS.notEmpty(insw) && insw == on) {
        on.print();
        app.pinModeOutput(pini);
        app.analogWrite(pini, 0);
        sw = insw;
        files.write(swf, on);
     } elseIf (TS.notEmpty(insw) && insw == off) {
        off.print();
        app.pinModeOutput(pini);
        app.analogWrite(pini, 255);
        sw = insw;
        files.write(swf, off);
     }
     return("ok");
   }
   
   clearStates() {
     if (files.exists(swf)) {
       files.delete(swf);
     }
   }

}
