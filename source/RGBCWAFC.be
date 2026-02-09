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

class Embedded:RGBCWCtl {

emit(cc_classHead) {
"""
std::unique_ptr<Adafruit_NeoPixel> rgbLed;
"""
}

   new(_ash, Int _conPos, String _conName, String _conArgs) {

     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int lastSwEvent = Int.new();
       String conArgs = _conArgs;
       Int zero = 0;
       Int twofidyfi = 255;
       String fifidy = "255,255,255,255,255"; //r,g,b,c,w
       String ok = CNS.ok;
       String on = CNS.on;
       String off = CNS.off;
       Int conPos = _conPos;
       String conName = _conName;
     }
     fields {
       Int lastEvent = Int.new();
       String rgbcw = fifidy;
       String sw = off;
     }
   }

   conTypeGet() String {
     return(conName);
   }

   initControl() {
     slots {
       String getrgbcw = "getrgbcw";
       String setrgbcw = "setrgbcw";
       String setsw = "setsw";
       String getsw = "getsw";
       Int ctrgbcwi;
       Int ctswi;
     }
     fields {
       Int np;
       Int ri;
       Int gi;
       Int bi;
       Int ci;
       Int wi;
     }

     ctswi = config.getPos("ct.sw." + conPos);

     ctrgbcwi = config.getPos("ct.rgbcwi." + conPos);

     np = app.strToInt(conArgs);

     emit(cc) {
        """
        int led_pin = bevp_np->bevi_int;
        rgbLed = std::make_unique<Adafruit_NeoPixel>(1, led_pin, NEO_GRB + NEO_KHZ800);
        """
      }

    String inrgbcw = config.get(ctrgbcwi);
    if (TS.notEmpty(inrgbcw)) {
      rgbcw = inrgbcw;
    }

    String insw = config.get(ctswi);
    if (TS.notEmpty(insw)) {
      sw = insw;
    } else {
      sw = on;
    }
    doState(List.new().addValue("dostate").addValue("notpw").addValue(conPos.toString()).addValue(setsw).addValue(sw));

   }

   doState(List cmdl) String {
     "in dostate fifidy".print();
     String scm = cmdl[3];
     if (scm == getsw) {
       return(sw);
     } elseIf (scm == getrgbcw) {
       return(rgbcw);
     } elseIf (scm == setsw) {
        String insw = cmdl[4];
        if (insw == on) {
          //check and off other control if present
          sw = insw;
          config.put(ctswi, on);
          //lastevent et all handled below in common with setrgb
        } elseIf (insw == off) {
          sw = insw;
          config.put(ctswi, off);
          //app.analogWrite(rp, zero);
          emit(cc) {
            """
            rgbLed->clear();
            rgbLed->show();
            """
          }
          "offed wrote zeros".print();
          lastEvent.setValue(ash.nowup);
          ash.lastEventsRes = null;
          return(ok);
        }
     } elseIf (scm == setrgbcw) {
        sw = on;
        rgbcw = cmdl[4];
        config.put(ctswi, on);
        config.put(ctrgbcwi, rgbcw);
     } else {
       return(ok);
     }
      ("rgbcw " + rgbcw).print();
      List rgbcwl = rgbcw.split(",");
      ri = app.strToInt(rgbcwl[0]);
      gi = app.strToInt(rgbcwl[1]);
      bi = app.strToInt(rgbcwl[2]);
      ci = app.strToInt(rgbcwl[3]);
      wi = app.strToInt(rgbcwl[4]);
      if (ri < zero || ri > twofidyfi) {
        ri = zero;
      }
      if (gi < zero || gi > twofidyfi) {
        gi = zero;
      }
      if (bi < zero || bi > twofidyfi) {
        bi = zero;
      }
      if (ci < zero || ci > twofidyfi) {
        ci = zero;
      }
      if (wi < zero || wi > twofidyfi) {
        wi = zero;
      }
      if (ri == twofidyfi && gi == twofidyfi && bi == twofidyfi) {
         /*app.analogWrite(rp, zero);
         app.analogWrite(gp, zero);
         app.analogWrite(bp, zero);
         app.analogWrite(cp, ci);
         app.analogWrite(wp, wi);*/
      } else {
        /*app.analogWrite(cp, zero);
        app.analogWrite(wp, zero);
        app.analogWrite(rp, ri);
        //("rp ri " + rp + " " + ri).print();
        app.analogWrite(gp, gi);
        //("gp gi " + gp + " " + gi).print();
        app.analogWrite(bp, bi);
        //("bp bi " + bp + " " + bi).print();*/
        emit(cc) {
            """
            int r = bevp_ri->bevi_int;
            int g = bevp_gi->bevi_int;
            int b = bevp_bi->bevi_int;
            rgbLed->setPixelColor(0, rgbLed->Color(r, g, b));
            rgbLed->show();
            //rgbLed->clear();
            """
          }
      }
      lastEvent.setValue(ash.nowup);
      ash.lastEventsRes = null;
      return(ok);
   }

   clearStates() {
     config.put(ctswi, on);
     config.put(ctrgbcwi, fifidy);
   }
   
}
