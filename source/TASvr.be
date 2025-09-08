/*
 * Copyright (c) 2024-2025, the Brace Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Math:Int;
use Math:Float;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:AppShell;
use Embedded:Config;

use Embedded:CommonNames as CNS;
use Embedded:Tad;

class Embedded:TAServer {

  new(_ash) self {
    slots {
      Embedded:AppShell ash = _ash;
      Config config = ash.config;
      Int tadi;
      List tads = List.new();
      String slashn = "\n";
      String slashr = "\r";
      String readBuf = String.new();
      Bool shouldSave = false;
      String swt = "sw";
      String rgbbt = "rgbcwsgd";
      Int myup = Int.new();
      Int forceDisco = 0;
    }
    fields {
      Bool didFail = false;
    }
  }

  handleCmdl(List cmdl) String {
         //so, need this:
         //act ept ondid ipos spass
         //add ool id ipos spass
         //rm ool id
        if (cmdl.length > 2 && cmdl[2] == "clear") {
          clearTads();
          //ash.needsFsRestart = true;
        } elseIf (cmdl.length > 2 && cmdl[2] == "startdis") {
          startDis();
        } elseIf (cmdl.length > 4 && cmdl[2] == "startdisr") {
          minDisIp = Int.new(cmdl[3]);
          maxDisIp = Int.new(cmdl[4]);
          startDis();
        } elseIf (cmdl.length > 2 && cmdl[2] == "testdt") {
          testDetectType();
        } elseIf (cmdl.length > 2 && cmdl[2] == "testgm") {
          testGetMac();
        } else {
          "bad tacmd".print();
          return("tacmdbad");
        }
        return("tacmdok");
  }

  startDis() {
    "startdis".print();
    String ip = Wifi.localIP;
    if (TS.notEmpty(ip)) {
      ("ip is " + ip).print();
      var ipl = ip.split(".");
      //("ipl len " + ipl.length).print();
      if (ipl.length == 4) {
        ip = ipl[0] + "." + ipl[1] + "." + ipl[2] + ".";
        disNetBase = ip;
      }
    }
    nextDisIp = minDisIp.copy();
    inDis = true;
  }

  saveTads() {
    if (tads.isEmpty) {
      "empty tads".print();
      config.put(tadi, "");
    } else {
      String mc = String.new();
      for (Tad tad in tads) {
        if (TS.notEmpty(mc)) {
          mc += "?";
        }
        mc += tad.etp += "," += tad.ina += "," += tad.wada;
      }
      ("conf putting mc " + mc).print();
      config.put(tadi, mc);
    }
  }

  loadTads() {
    String mcs = config.get(tadi);
    if (TS.notEmpty(mcs)) {
      var mce = mcs.split("?");
      for (String mc in mce) {
        var mcl = mc.split(",");
        tads += Tad.new(mcl[0], mcl[1], mcl[2]);
        ("added Tad " + mc).print();
      }
      regenControls();
    }
  }

  //String cmds = "dostate spass " + ipos + " setsw " + state + " e";
  //also need kdname/ondid
  //so, need this:
  //matrtype,ondid,spass,ipos
  //also, is it add, remove, or clear

  clearTads() {
    config.put(tadi, "");
  }

  start() {
    tadi = config.getPos("eh.tads");
    "loading tads".print();
    loadTads();

    Int tadslen = tads.length;

    for (Int i = 0;i < tadslen;i++) {
      if (i >= 15) {
        break;
      }
      Tad tad = tads[i];
      if (def(tad)) {
      }
    }

    if (tadslen <= 0) { Int ivdiv = 1; } else { ivdiv = tadslen; }
    slots {
      Int failCheckIv = 1200000; //millis per fail check and rescan 600000 10 mins 1200000 20 mins
      Int discoRpt = 9;
      //Int failCheckIv = 30000;
      Int nextFailCheck = ash.nowup + failCheckIv;
      Int disCheckIv = 250; //ms pause between checks when scanning ffor devices
      Int nextDisCheck = ash.nowup + disCheckIv;
      Int nextDisIp = 1;
      Int maxDisIp = 255;
      Int minDisIp = 1;
      //Int maxDisIp = 199;
      //Int minDisIp = 147;
      String disNetBase;
      String templ = "/cm?cmnd=Template";
      String macgt = "/cm?cmnd=Status%205";
      String htp = "http://";
      Bool inDis = false;
    }

  }

  checkNDo() {
    if (shouldSave) {
      shouldSave = false;
      saveTads();
      return(self);
    }
    Int didact;
    if (undef(didact)) {
      Int nowup = ash.nowup;
      if (def(nextFailCheck) && nowup > nextFailCheck) {
        nextFailCheck = nowup + failCheckIv;
        if (didFail) {
          didFail = false;
          startDis();
        } else {
          forceDisco++;
          if (forceDisco > discoRpt) {
            forceDisco = 0;
            didFail = true;
          }
        }
      } elseIf (def(inDis) && inDis && nowup > nextDisCheck && TS.notEmpty(disNetBase)) {
        nextDisCheck = nowup + disCheckIv;
        //"disCheck".print();
        //scan addresses 1 through 254 inclusive
        String turl = htp + disNetBase + nextDisIp + templ;
        String disRes = httpGetRetry(turl);
        if (TS.notEmpty(disRes)) {
          //("disRes " + disRes).print();
          String ft = detectType(disRes);
          disRes = null;
          if (TS.notEmpty(ft)) {
            turl = htp + disNetBase + nextDisIp + macgt;
            disRes = httpGetRetry(turl);
            if (TS.notEmpty(disRes)) {
              //("disRes2 " + disRes).print();
              String mac = getMac(disRes);
            }
        }
        if (TS.notEmpty(ft) && TS.notEmpty(mac)) {
          ("got ft and mac " + ft + " " + mac).print();
          turl = htp + disNetBase + nextDisIp;
          upsertTad(ft, mac, turl);
        }
        }
        ash.app.uptime(myup);
        nextDisCheck = myup + disCheckIv;
        nextDisIp++;
        if (nextDisIp >= maxDisIp) {
          inDis = false;
          nextDisIp = minDisIp.copy();
        }
      }
    }
  }

  httpGetRetry(String turl) String {
     for (Int i = 0;i < 3;i++) {
       String res = httpGet(turl);
       if (TS.notEmpty(res)) {
         return(res);
       }
       //ash.app.delay(5);
     }
     return(null);
   }

  httpGet(String turl) String {
    ("turl " + turl).print();
    String disRes;
        emit(cc) {
          """
#ifdef BEAR_ESP8266
WiFiClient client;
HTTPClient http;
http.begin(client, beq->beva_turl->bems_toCcString().c_str());
#endif
#ifdef BEAR_ESP32
  HTTPClient http;
  http.setConnectTimeout(500);
  //http.setConnectTimeout(750);
  http.begin(beq->beva_turl->bems_toCcString().c_str());
  http.setTimeout(1000);
  //http.setTimeout(1500);
#endif
  int httpCode = http.GET();
  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      if (payload.length() > 0) {
        Serial.println(payload);
        std::string lips = std::string(payload.c_str());
        beq->bevl_disRes = new BEC_2_4_6_TextString(lips);
      }
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
          """
        }
    return(disRes);
  }

  testGetMac() {
     /*String mac1 = getMac('{"StatusNET":{"Hostname":"tasmota","IPAddress":"192.168.4.48","Gateway":"192.168.4.1","Subnetmask":"255.255.255.0","DNSServer1":"0.0.0.0","DNSServer2":"0.0.0.0","Mac":"40:4C:30:31:32:33","Webserver":2,"HTTP_API":1,"WifiConfig":4,"WifiPower":19.0}}');
     if (TS.notEmpty(mac1)) {
       ("mac1 " + mac1).print();
     }*/
  }

  getMac(String disRes) String {
    String res;
    if (TS.notEmpty(disRes)) {
      ("getMac " + disRes).print();
      var drl = disRes.split(":");
      Int mcnt = 0;
      for (String dr in drl) {
        //("dr " + dr).print();
        if (mcnt > 0) {
          res+= dr;
          mcnt--;
        }
        if (dr.has('"Mac"')) {
          mcnt = 6;
          res = String.new();
        }
      }
    }
    if (TS.notEmpty(res)) {
      var resl = res.split('"');
      //for (String r in resl) {
      //  ("r " + r).print();
      //}
      if (resl.length > 1) {
        res = resl[1];
      }
    }
    return(res);
  }

  testDetectType() {
    /*String r1 = detectType('{"NAME":"Athom Plug V3","GPIO":[0,0,0,32,0,224,576,0,0,0,0,0,0,0,0,0,0,0,0,0,3104,0],"FLAG":0,"BASE":1}');
    String r2 = detectType('{"NAME":"Athom 15W Bulb","GPIO":[0,0,0,0,416,419,0,0,417,452,418,0,0,0],"FLAG":0,"BASE":18}');
    if (TS.isEmpty(r1) || TS.isEmpty(r2)) {
      ("tdt had empty").print();
    } else {
      ("r1 " + r1 + " r2 " + r2).print();
    }*/
  }

  detectType(String disRes) String {
    String res;
    if (TS.notEmpty(disRes)) {
      ("disRes " + disRes).print();
      var drl = disRes.split(":");
      Bool gpnext = false;
      for (String dr in drl) {
        //("dr " + dr).print();
        if (gpnext) {
          gpnext = false;
          //"has gpio".print();
          Int fb = dr.find("[");
          Int lb = dr.find("]");
          if (def(fb) && def(lb) && lb > fb) {
            //"gping".print();
            String gp = dr.substring(fb + 1, lb);
            //("gp " + gp).print();
            Int rlc = 0;//relay count, 200-300, 20-30
            Int pwc = 0;//pwm count, 400-500
            var gpl = gp.split(",");
            for (String gpi in gpl) {
              //("gpi " + gpi).print();
              if (gpi.isInteger) {
                Int gpii = Int.new(gpi);
                if (gpii >= 200 && gpii < 300) {
                 //"relay1".print();
                 rlc++;
                } elseIf (gpii >= 20 && gpii < 30) {
                  //"relay2".print();
                  rlc++;
                } elseIf (gpii >= 400 && gpii < 500) {
                  //"pwm1".print();
                  pwc++;
                }
              }
            }
            if (pwc == 5) {
              res = rgbbt;
            } elseIf (rlc == 1) {
              res = swt;
            }
          }
        }
        if (dr.has('"GPIO"')) {
          gpnext = true;
        }
      }
    }
    return(res);
  }

  upsertTad(String etp, String ina, String wada) {
    if (TS.notEmpty(etp) && TS.notEmpty(ina) && TS.notEmpty(wada)) {
      Bool found = false;
      for (Tad tad in tads) {
        if (def(tad)) {
          if (tad.ina == ina) {
            found = true;
            //"found checking wada".print();
            if (tad.wada != wada) {
              tad.wada = wada;
              shouldSave = true;
              "upd wada".print();
            }
          }
        }
      }
      unless (found) {
        tad = Tad.new(etp, ina, wada);
        tads += tad;
        shouldSave = true;
        ("in upsertTad adding " + ina + " " + wada).print();
        regenControls();
      }
    }
  }

  handleLoop() {
   checkNDo();
  }

  regenControls() {
    Int conPos = 0;
    for (Tad tad in tads) {
      if (tad.etp == swt) {
        var tasc = Embedded:TaSc.new(ash, conPos, tad, self);
        tasc.initControl();
        ash.controls[conPos] = tasc;
        conPos = conPos + 1;
      } elseIf (tad.etp == rgbbt) {
        var tabc = Embedded:TaRgbbc.new(ash, conPos, tad, self);
        tabc.initControl();
        ash.controls[conPos] = tabc;
        conPos = conPos + 1;
      }
    }
    ash.genControlDef();
  }

}

class Embedded:TaSc {

   new(_ash, Int _conPos, Tad _tad, Embedded:TAServer _taserver) {
     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int conPos = _conPos;
       String conType = _tad.etp;
       Tad tad = _tad;
       Embedded:TAServer taserver = _taserver;
       String ok = CNS.ok;
       String ud = CNS.undefined;
       String uon = "/cm?cmnd=Power%20On";
       String uoff = "/cm?cmnd=Power%20Off";
     }
     fields {
       Int lastEvent = Int.new();
     }
   }

   conTypeGet() String {
     return(conType);
   }


   initControl() {
     slots {
       Int scswi;
       String getsw = "getsw";
       String on = CNS.on;
       String off = CNS.off;
       String setsw = "setsw";
     }
     fields {
       String sw;
     }
     scswi = config.getPos("sc.sw." + conPos);

     String insw = config.get(scswi);
     if (TS.notEmpty(insw)) {
       sw = insw;
     }
   }

   doState(List cmdl) String {
     "in dostate".print();
     String dsr = ok;
     String scm = cmdl[3];
     if (scm == getsw) {
      if (TS.notEmpty(sw)) {
        return(sw);
        } else {
        return(ud);
        }
     } elseIf (scm == setsw) {
       //curl http://192.168.4.7/cm?cmnd=Power%20On
       //curl http://192.168.4.7/cm?cmnd=Power%20Off
        String insw = cmdl[4];
        if (insw == on) {
          sw = insw;
          on.print();
          String turl = tad.wada + uon;
          String disRes = taserver.httpGetRetry(turl);
          if (TS.notEmpty(disRes) && disRes.lowerValue().has("on")) {
            config.put(scswi, on);
          } else {
            dsr = CNS.fail;
            taserver.didFail = true;
          }
        } elseIf (insw == off) {
          sw = insw;
          off.print();
          turl = tad.wada + uoff;
          disRes = taserver.httpGetRetry(turl);
          if (TS.notEmpty(disRes) && disRes.lowerValue().has("off")) {
            config.put(scswi, off);
          } else {
            dsr = CNS.fail;
            taserver.didFail = true;
          }
        }
        if (TS.notEmpty(disRes)) {
          ("setsw disRes " + disRes).print();
        }
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     }
     return(dsr);
   }

   clearStates() {
     config.put(scswi, off);
   }

}

class Embedded:TaRgbbc {

    new(_ash, Int _conPos, Tad _tad, Embedded:TAServer _taserver) {
     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int conPos = _conPos;
       String conType = _tad.etp;
       Tad tad = _tad;
       Embedded:TAServer taserver = _taserver;
       String ok = CNS.ok;
       String ud = CNS.undefined;
       String uon = "/cm?cmnd=Power%20On";
       String uoff = "/cm?cmnd=Power%20Off";
       String fifidy = "255,255,255,255,255"; //r,g,b,c,w
       String on = CNS.on;
       String off = CNS.off;
     }
     fields {
       Int lastEvent = Int.new();
       String rgbcw = fifidy;
       String sw = off;
     }
   }

   conTypeGet() String {
     return(conType);
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

     ctswi = config.getPos("ct.sw." + conPos);

     ctrgbcwi = config.getPos("ct.rgbcwi." + conPos);

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

   }

   lsToMired(Int ls) Int {
      if (ls < 0 || ls > 255) { ls = 255; }
      Float lsf = Float.intNew(ls);
      Float fh = Float.intNew(255);
      Float mp = lsf / fh;
      Float mrm = Float.intNew(347);
      Float mrf = mp * mrm;
      Int mr = mrf.toInt();
      mr = mr + 153;
      return(mr);
    }

    lvlToPct(Int ls) Int {
      if (ls < 0 || ls > 255) { ls = 255; }
      Float lsf = Float.intNew(ls);
      Float fh = Float.intNew(255);
      Float mp = lsf / fh;
      Float mrm = Float.intNew(100);
      Float mrf = mp * mrm;
      Int mr = mrf.toInt();
      return(mr);
    }

   doState(List cmdl) String {
     "in dostate fifidy".print();
     String dsr = ok;
     String scm = cmdl[3];
     if (scm == getsw) {
       return(sw);
     } elseIf (scm == getrgbcw) {
       return(rgbcw);
     } elseIf (scm == setsw) {
       //curl http://192.168.4.7/cm?cmnd=Power%20On
       //curl http://192.168.4.7/cm?cmnd=Power%20Off
        String insw = cmdl[4];
        if (insw == on) {
          sw = insw;
          on.print();
          String turl = tad.wada + uon;
          String disRes = taserver.httpGetRetry(turl);
          if (TS.notEmpty(disRes) && disRes.lowerValue().has("on")) {
            config.put(ctswi, on);
          } else {
            dsr = CNS.fail;
            taserver.didFail = true;
          }
        } elseIf (insw == off) {
          sw = insw;
          off.print();
          turl = tad.wada + uoff;
          disRes = taserver.httpGetRetry(turl);
          if (TS.notEmpty(disRes) && disRes.lowerValue().has("off")) {
            config.put(ctswi, off);
          } else {
            dsr = CNS.fail;
            taserver.didFail = true;
          }
        }
        if (TS.notEmpty(disRes)) {
          ("setsw disRes " + disRes).print();
        }
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     } elseIf (scm == setrgbcw) {
        sw = on;
        rgbcw = cmdl[4];
        if (TS.notEmpty(rgbcw)) {
          config.put(ctswi, on);
          config.put(ctrgbcwi, rgbcw);
          ("rgbcw " + rgbcw).print();
          var rgbcwl = rgbcw.split(",");
          if (rgbcwl.length > 4) {
            if (rgbcw.begins("255,255,255")) {
              "do cw".print();
              Int cti = Int.new(rgbcwl[4]);
              cti = 255 - cti;
              ("cti 2 " + cti).print();
              cti = lsToMired(cti);
              ("cti 3 " + cti).print();
              Int lvli = Int.new(rgbcwl[3]);
              lvli = lvlToPct(lvli);
              if (lvli < 1) { lvli = 1; }
              ("lvli 2 " + lvli).print();
              String lcm = "/cm?cmnd=backlog%20Dimmer%20" + lvli  + "%3BCT%20" + cti;
              ("ct lcm " + lcm).print();
            } else {
              "do rgb".print();
              lcm = "/cm?cmnd=Color%20" + rgbcwl[0] + "%2C" + rgbcwl[1] + "%2C" + rgbcwl[2];
            }
            turl = tad.wada + lcm;
            //("turl " + turl).print();
            disRes = taserver.httpGetRetry(turl);
          } else {
           "rgbcwl too short".print();
          }
          if (TS.notEmpty(disRes) && (disRes.has("Color") || disRes.has("{}"))) {
            //config.put(ctswi, off);
            ("disRes " + disRes).print();
            config.put(ctswi, on);
            config.put(ctrgbcwi, rgbcw);
          } else {
            dsr = CNS.fail;
            taserver.didFail = true;
          }
        } else {
          "something undef".print();
        }
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     }
     return(dsr);
   }

   clearStates() {
     config.put(ctswi, on);
     config.put(ctrgbcwi, fifidy);
   }

}
