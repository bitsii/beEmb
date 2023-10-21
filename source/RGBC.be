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

class Embedded:RGBControl {

   new(_ash, Int _conPos, String _conName, String _conArgs) {

     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int lastSwEvent = Int.new();
       String conArgs = _conArgs;
       Int zero = 0;
       Int twofity = 255;
       String ok = "ok";
     }
     fields {
       Int conPos = _conPos;
       Int lastEvent = Int.new();
       String conName = _conName;
     }

   }

   initControl() {
     slots {
       String on = "on";
       String off = "off";
       String brightness = "brightness";
       String color = "color";
       String ON = "ON";
       String OFF = "OFF";
       String getrgb = "getrgb";
       String setrgb = "setrgb";
       String setsw = "setsw";
       String getsw = "getsw";
       Int rp;
       Int gp;
       Int bp;
       Int rmq; Int gmq; Int bmq;
       Int lvlmq;
       Int rgbrgbi;
       Int rgbswi;
     }
     fields {
       String rgb;
       String sw;
     }

     rgbrgbi = config.getPos("rgb.rgb." + conPos);
     rgbswi = config.getPos("rgb.sw." + conPos);

     if (conArgs.has(",")) {
        auto cal = conArgs.split(",");
        if (cal.size < 3) {
          "not enough pins for rgbc".print();
        }
        rp = app.strToInt(cal[0]);
        gp = app.strToInt(cal[1]);
        bp = app.strToInt(cal[2]);
     }

    String inrgb = config.get(rgbrgbi);
    if (TS.notEmpty(inrgb)) {
      rgb = inrgb;
    }

    String insw = config.get(rgbswi);
    if (TS.notEmpty(insw)) {
      sw = insw;
      doState(List.new().addValue("dostate").addValue("notpw").addValue(conPos.toString()).addValue(setsw).addValue(sw));
    }

   }

   doMqConf(mqtta, String qpref, String did, String dname, Bool doSubs) {
     ifNotEmit(noMqtt) {
      Embedded:Mqtt mqtt = mqtta;
      String conPoss = conPos.toString();
      String tpp = qpref + "/light/" + did + "-" + conPoss;
      String pt = tpp + "/config";
      String cf = "{ \"name\": \"" += dname += " " += conPoss += "\", \"command_topic\": \"" += tpp += "/set\", \"state_topic\": \"" += tpp += "/state\", \"unique_id\": \"" += did += "-" += conPoss += "\", \"schema\": \"json\", \"brightness\": true, \"rgb\": true, \"color_temp\": false }";//trying for rgbcct
      if (doSubs) {
        mqtt.subscribeAsync(tpp += "/set");
      }
      mqtt.publishAsync(pt, cf);
     }
   }

   doMqStatePub(mqtta, String qpref, String did) {
     ifNotEmit(noMqtt) {
        Embedded:Mqtt mqtt = mqtta;
        String conPoss = conPos.toString();
        String tpp = qpref + "/light/" + did + "-" + conPoss;
        String pt = tpp + "/state";
        String cf = "{ \"state\": \"";
        if (TS.notEmpty(sw)) {
          cf += sw.upper();
        } else {
          cf += OFF;
        }
        cf += "\"";
        if (def(lvlmq)) {
          cf += ", \"brightness\": " += lvlmq.toString();
        }
        cf += " }";
        mqtt.publishAsync(pt, cf);
     }
   }

   doMqState(String topic, String payload) String {
     //("in doMqState rgb " + topic + " " + payload).print();
     Int stok = payload.find(brightness);
     Int ctok = payload.find(color);
     if (def(stok) ) {
       payload = payload.substring(stok, payload.size);
       stok = payload.find(":");
       if (def(stok)) {
         payload = payload.substring(stok + 1, payload.size);
         stok = payload.find("}");
         if (def(stok)) {
           payload = payload.substring(0, stok);
         }
         stok = payload.find(",");
         if (def(stok)) {
           payload = payload.substring(0, stok);
         }
         //("brightness |" + payload + "|").print();
         lvlmq = app.strToInt(payload);
         //List ds = List.new() += "na" += "na" += "na" += setrlvll += payload;
         //return(doState(ds));
       }
     } elseIf (def(ctok) ) {
       //{"state":"ON","color":{"r":255,"g":28,"b":54}}
       payload = payload.substring(ctok, payload.size);
       Int btok = payload.find("{");
       Int etok = payload.find("}");
       if (def(btok) && def(etok)) {
         btok++=;
         payload = payload.substring(btok, etok);
         List cvs = payload.split(",");
         for (String cv in cvs) {
           List icv = cv.split(":");
           if (icv.size > 1) {
             //"got icv".print();
             //icv[0].print();
             //icv[1].print();
             if (icv[0] == '"r"') {
               rmq = app.strToInt(icv[1]);
             } elseIf (icv[0] == '"g"') {
               gmq = app.strToInt(icv[1]);
             } elseIf (icv[0] == '"b"') {
               bmq = app.strToInt(icv[1]);
             }
           }// else {
           //  "bad icv".print();
           //}
         }
       }// else {
       //  "bad btok etok".print();
       //}
     } elseIf (payload.has(ON)) {
       List ds = List.new() += "na" += "na" += "na" += setsw += on;
       return(doState(ds));
     } elseIf (payload.has(OFF)) {
       ds = List.new() += "na" += "na" += "na" += setsw += off;
       return(doState(ds));
     }
     return(null);
   }

   doState(List cmdl) String {
     "in dostate rgb".print();
     String scm = cmdl[3];
     if (scm == getsw) {
        if (TS.notEmpty(sw)) {
          return(sw);
        } else {
          return("undefined");
        }
     } elseIf (scm == getrgb) {
      if (TS.notEmpty(rgb)) {
        return(rgb);
      } else {
        return("undefined");
      }
     } elseIf (scm == setsw) {
        String insw = cmdl[4];
        if (insw == on) {
          if (TS.isEmpty(rgb)) {
            rgb = "255,255,255";
          }
          //check and off other control if present
          sw = insw;
          config.put(rgbswi, on);
          //lastevent et all handled below in common with setrgb
        } elseIf (insw == off) {
          sw = insw;
          config.put(rgbswi, off);
          app.analogWrite(rp, zero);
          app.analogWrite(gp, zero);
          app.analogWrite(bp, zero);
          "offed wrote zeros".print();
          lastEvent.setValue(ash.nowup);
          ash.lastEventsRes = null;
          ifNotEmit(noMqtt) {
            ash.needsStateUp = true;
          }
          return(ok);
        }
     } elseIf (scm == setrgb) {
        //check and off other control if present
        sw = on;
        rgb = cmdl[4];
        config.put(rgbswi, on);
        config.put(rgbrgbi, rgb);
     } else {
       return(ok);
     }
      ("rgb " + rgb).print();
      List rgbl = rgb.split(",");
      Int ri = app.strToInt(rgbl[0]);
      Int gi = app.strToInt(rgbl[1]);
      Int bi = app.strToInt(rgbl[2]);
      if (ri < zero || ri > twofity) {
        ri = zero;
      }
      if (gi < zero || gi > twofity) {
        gi = zero;
      }
      if (bi < zero || bi > twofity) {
        bi = zero;
      }
      app.analogWrite(rp, ri);
      //("rp ri " + rp + " " + ri).print();
      app.analogWrite(gp, gi);
      //("gp gi " + gp + " " + gi).print();
      app.analogWrite(bp, bi);
      //("bp bi " + bp + " " + bi).print();
      lastEvent.setValue(ash.nowup);
      ash.lastEventsRes = null;
      ifNotEmit(noMqtt) {
        ash.needsStateUp = true;
      }
      return(ok);
   }

   clearStates() {
     config.put(rgbswi, off);
     config.put(rgbrgbi, "255,255,255");
   }
   
}
