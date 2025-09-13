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
use Embedded:Hqd;

class Embedded:Hqb {

  new(_ash) self {
    slots {
      Embedded:AppShell ash = _ash;
      Config config = ash.config;
      Int hdi;
      List hds = List.new();
      String slashn = "\n";
      String slashr = "\r";
      String readBuf = String.new();
      Bool brdCh = false;
      Int zero = 0;
      Int nextPubState = zero;
    }
    fields {
      Bool timeToDecom = false;
    }
  }

  handleCmdl(List cmdl) String {
         //so, need this:
         //act ept ondid ipos spass
         //add ool id ipos spass
         //rm ool id
        if (cmdl.length > 2 && cmdl[2] == "clear") {
          clearHds();
          //ash.needsFsRestart = true;
        } elseIf (cmdl.length > 2 && cmdl[2] == "chrestart") {
          if (brdCh) {
            "will restart chrestart".print();
            brdCh = false;
            ash.needsFsRestart = true;
          }
        } elseIf (cmdl.length > 2 && cmdl[2] == "rmold") {
          nx = List.new();
          nowup = ash.nowup;
          if (def(nowup)) {
            for (hd in hds) {
              if (undef(hd.lastUp) || nowup - hd.lastUp > 60000) {
                "rmold removing a device".print();
                brdCh = true;
              } else {
                 nx += hd;
              }
            }
          }
          hds = nx;
          saveHds();
        } elseIf (cmdl.length > 3) {
          Int nowup = ash.nowup;
          String act = cmdl[2];
          if (act == "add" && cmdl.length > 6) {
            if (hds.length >= 15) {
              return("brdtoomany");
            }
            for (Hqd hd in hds) {
              if (hd.ondid == cmdl[4] && hd.ipos == cmdl[5]) {
                "brd add sent a dupe".print();
                hd.lastUp = nowup;
                return("brdok");
              }
            }
            brdCh = true;
            Hqd addh = Hqd.new(cmdl[3], cmdl[4], cmdl[5], cmdl[6]);
            addh.lastUp = nowup;
            hds += addh;
            saveHds();
            //ash.needsFsRestart = true;
          } elseIf (act == "rm" && cmdl.length > 5) {
            List nx = List.new();
            for (hd in hds) {
              if (hd.ondid == cmdl[4] && hd.ipos == cmdl[5]) {
                brdCh = true;
              } else {
                nx += hd;
              }
            }
            hds = nx;
            saveHds();
            //ash.needsFsRestart = true;
          } else {
            ("unknown brd act " + act).print();
            return("brdbadact");
          }
        } else {
          "bad brd cmd".print();
          return("brdbadcmd");
        }
        return("brdok");
  }

  subscribe() {
    "hbserver in subscribe".print();
    ash.smcserver.subscribe("homeassistant/status");
    subDevices();
    pubDevices();
  }

  cwForCwLvl(Int rsi, Int l) {
    if (rsi == 127) {
      Int c = 255;
      Int w = 255;
    } elseIf (rsi < 127) {
      c = 255;
      w = rsi * 2; //127 == 254, 120 == 240, 64 == 128, 32 == 64, 16 == 8, 8 == 16, 4 == 8
    } elseIf (rsi > 127) {
      //254 == 2, 128 == 254, 134 == 240,
      Int rsii = 255 - rsi;//128 == 127, 127+7=134,255-134=121,127+64= 255-251=4
      c = rsii * 2; //127 == 254, 121 == 242, 64 == 128, 32 == 64
      w = 255;
    }
    //c and w scaled to lvl/255
    Float tff = Float.intNew(255);
    Float cf = Float.intNew(c);
    Float wf = Float.intNew(w);
    Float lf = Float.intNew(l);
    Float mpl = lf / tff;
    Float fcf = cf * mpl;
    Float fwf = wf * mpl;
    Int fc = fcf.toInt();
    Int fw = fwf.toInt();
    if (fc < 1 && c > 0) { fc = 1; }
    if (fw < 1 && w > 0) { fw = 1; }
    String res = fc.toString() + "," + fw.toString();
    return(res);
  }

  cwForCwsLvl(Int cwi, Int lvli) {
    if (lvli < 0 || lvli > 255) { lvli = 255; }
    if (lvli == 1) { lvli = 2; } //cws seems to be off at analog write 1
    if (cwi < 0 || cwi > 255) { cwi = 255; }
    cwi = 255 - cwi;
    String res = lvli.toString() + "," + cwi.toString();
    return(res);
  }

  handleMessage(String top, String msg) {
    "hbsserver in handleMessage".print();
    if (TS.notEmpty(top) && TS.notEmpty(msg)) {
      ("top " + top + " msg " + msg).print();
      if (top.begins("homeassistant/") && top.ends("/set")) {
        var ll = top.split("/");
        String didpos = ll[2];
        var dp = didpos.split("-");
        Int hdi = Int.new(dp[1]);
        if (def(hds)) {
          Hqd hd = hds[hdi];
          if (def(hd) && TS.notEmpty(hd.met)) {
            if (hd.met == "ool") {
              String mlow = msg.lower();
              String scmds = "sp2 " + doSec(hd.spass) + " dostate X " + hd.ipos + " setsw " + mlow + " e";
              String scres = sendCmd(hd, scmds);
              if (TS.notEmpty(scres)) {
                ("scres " + scres).print();
                if (scres.has(CNS.ok)) {
                  var tl = top.split("/");
                  String stpp = "homeassistant/switch/" + tl[2] + "/state";
                  ash.smcserver.publish(stpp, msg);
                  if (mlow == CNS.on) {
                  hd.sw = true;
                  } else {
                  hd.sw = false;
                  }
                }
              }
            } elseIf (hd.met.begins("ecl")) {
              "got ecl set".print();
              tl = top.split("/");

              if (msg.has("\"ON\"")) {
                hd.sw = true;
              } elseIf (msg.has("\"OFF\"")) {
                hd.sw = false;
              }

              for (String cs in msg.split(",")) {
                //("cs " + cs).print();
                if (cs.has("\"brightness\"")) {
                  Int c = cs.find(":");
                  Int e = cs.find(",");
                  if (undef(e)) {
                    e = cs.find("}");
                  }
                  if (def(c) && def(e)) {
                    String bi = cs.substring(c + 1, e);
                    Int b = Int.new(bi);
                    hd.lvl = b;
                    ("set lvl to " + b).print();
                  }
                }
                if (cs.has("\"color_temp\"")) {
                  c = cs.find(":");
                  e = cs.find(",");
                  if (undef(e)) {
                    e = cs.find("}");
                  }
                  if (def(c) && def(e)) {
                    String ti = cs.substring(c + 1, e);
                    Int t = Int.new(ti);
                    hd.ct = t;
                    ("set ct to " + t).print();
                    hd.inCt = true;
                  }
                }
                if (cs.has("\"h\"")) {
                  Int hih = cs.find("\"h\"");
                  Int hic = cs.find(":", hih);
                  if (def(hic)) {
                    Int hip = cs.find(".", hic);
                    if (def(hip)) {
                      String his = cs.substring(hic + 1, hip);
                      Int hi = Int.new(his);
                      hd.h = hi;
                      ("set h to " + hi).print();
                      hd.inCt = false;
                    }
                  }
                }
                if (cs.has("\"s\"")) {
                  Int sih = cs.find("\"s\"");
                  Int sic = cs.find(":", sih);
                  if (def(sic)) {
                    Int sip = cs.find(".", sic);
                    if (def(sip)) {
                      String sis = cs.substring(sic + 1, sip);
                      Int si = Int.new(sis);
                      hd.s = si;
                      ("set s to " + si).print();
                    }
                  }
                }
              }

              if (undef(hd.sw)) { hd.sw = false; }
              if (undef(hd.inCt)) { hd.inCt = false; }
              if (hd.sw) {
                if (hd.inCt) {
                  //on with temp
                  //500 - 153

                  if (undef(hd.lvl)) { hd.lvl = 255; }
                  Int ebb = hd.lvl;
                  Int ewt = miredToLs(hd.ct);

                  xd = "255,255,255," += ebb; //,cw
                  String xd += "," += ewt;

                  if (hd.met == "ecl") {
                    rgblct = "255,255,255," += cwForCwsLvl(ewt, ebb);
                  } elseIf (hd.met == "eclns") {
                    rgblct = "255,255,255," += cwForCwLvl(ewt, ebb);
                  }

                  scmds = "sp2 " + doSec(hd.spass) + " dostatexd X " + hd.ipos + " setrgbcw " + rgblct + " " + xd + " " + " e";
                } else {
                  //on with color
                  hsvToRgb(hd);
                  String rgblct = "" += hd.r += "," += hd.g += "," += hd.b += "," += hd.lvl += ",0";//last 0 is cw for rgb case
                  scmds = "sp2 " + doSec(hd.spass) + " dostatexd X " + hd.ipos + " setrgbcw " + rgblct + " " + rgblct + " " + " e";
                }
              } else {
                //turn off
                mlow = "off";
                scmds = "sp2 " + doSec(hd.spass) + " dostate X " + hd.ipos + " setsw " + mlow + " e";
              }
              if (TS.notEmpty(scmds)) {
                scres = sendCmd(hd, scmds);
                if (TS.notEmpty(scres)) {
                  ("scres " + scres).print();
                  if (scres.has(CNS.ok)) {
                    pubEcl(hd, tl[2]);
                  }
                }
              }
            }
          }
        }
      } elseIf (top == "homeassistant/status" && msg == "online") {
        pubDevices();
      }
    }
  }

  miredToLs(Int mr) Int {
    if (mr < 153 || mr > 500) { mr = 153; }
    Int mrb = mr - 153;
    Float mrbf = Float.intNew(mrb);
    Float fh = Float.intNew(347);
    Float mp = mrbf / fh;
    Float lsm = Float.intNew(255);
    Float lsf = mp * lsm;
    Int ls = lsf.toInt();
    return(ls);
  }

  hsvToRgb(Hqd hd) {
    //Hue (h) → 0–360 Saturation (s) → 0–100 Brightness (brightness) → 0–255
    // * Assumes h, s, and v are contained in the set [0, 1] and
    // * returns r, g, and b in the set [0, 255].

    Float sixf = Float.intNew(6);
    Float onef = Float.intNew(1);
    Float tff = Float.intNew(255);
    Float tsf = Float.intNew(360);
    Float ohf = Float.intNew(100);

    if (undef(hd.h)) { hd.h = 0; }
    if (undef(hd.s)) { hd.s = 0; }
    if (undef(hd.lvl)) { hd.lvl = 255; }

    Int hi = hd.h;
    Int si = hd.s;
    Int vi = hd.lvl;

    if (hi > 359 || hi < 0) { hi = 0; }

    Int i = hi / 60;
    Float h = Float.intNew(hi) / tsf;
    Float s = Float.intNew(si) / ohf;
    Float v = Float.intNew(vi) / tff;

    Float f = h * sixf - Float.intNew(i);
    Float p = v * (onef - s);
    Float q = v * (onef - f * s);
    Float t = v * (onef - (onef - f) * s);

    Float r; Float g; Float b;

    if (i == 0) {
      r = v; g = t; b = p;
    } elseIf (i == 1) {
      r = q; g = v; b = p;
    } elseIf (i == 2) {
      r = p; g = v; b = t;
    } elseIf (i == 3) {
      r = p; g = q; b = v;
    } elseIf (i == 4) {
      r = t; g = p; b = v;
    } elseIf (i == 5) {
      r = v; g = p; b = q;
    }

    hd.r = (r * tff).toInt();
    hd.g = (g * tff).toInt();
    hd.b = (b * tff).toInt();

  }

  checkPubStates() Bool {
    if (nextPubState > zero && ash.nowup > nextPubState) {
      "time to pubState".print();
      nextPubState = zero;
      if (def(hds)) {
        Int hdslen = hds.length;
        for (Int i = 0;i < hdslen;i++) {
          if (i >= 15) {
            break;
          }
          Hqd hd = hds[i];
          if (def(hd)) {
            if (hd.met == "ool") {
              "pubbing ool".print();
              String uid = hd.ondid + "-" + i;
              String tpp = "homeassistant/switch/" + uid;
              if (def(hd.sw) && hd.sw) {
                String st = "ON";
              } else {
                st = "OFF";
              }
              ash.smcserver.publish(tpp + "/state", st);
            } elseIf (hd.met.begins("ecl")) {
              uid = hd.ondid + "-" + i;
              pubEcl(hd, uid);
            }
          }
        }
      }
      return(true);
    }
    return(false);
  }

  pubEcl(Hqd hd, String uid) {
   "pubbing ecl".print();
    String tpp = "homeassistant/light/" + uid;
    if (def(hd.sw) && hd.sw) {
      String st = "ON";
    } else {
      st = "OFF";
    }
    if (undef(hd.h)) { hd.h = 0; }
    if (undef(hd.s)) { hd.s = 0; }
    if (undef(hd.lvl)) { hd.lvl = 255; }
    //String jst = "{\"state\":\"" += st += "\",\"brightness\":" += hd.lvl += ",\"color\":{\"r\":" += hd.r += ",\"g\":" += hd.g += ",\"b\":" += hd.b += "}}";
    //String jst = "{\"state\":\"" += st += "\"}";

    if (def(hd.inCt) && hd.inCt) {
      String jst = "{\"state\":\"" += st += "\",\"brightness\":" += hd.lvl += ",\"color_mode\":\"color_temp\",\"color_temp\":" += hd.ct += "}";
    } else {
      jst = "{\"state\":\"" += st += "\",\"brightness\":" += hd.lvl += ",\"color_mode\":\"hs\",\"color\":{\"h\":" += hd.h += ".0,\"s\":" += hd.s += ".0}}";
    }

    ("ecl " + jst).print();
    ash.smcserver.publish(tpp + "/state", jst);
    //dps.put("brightness", Int.new(lv));
    //dps.put("color_temp", lsToMired(Int.new(cw)));
  }

  subDevices() {
    if (def(hds)) {
      Int hdslen = hds.length;
      for (Int i = 0;i < hdslen;i++) {
        if (i >= 15) {
          break;
        }
        Hqd hd = hds[i];
        if (def(hd)) {
          if (hd.met == "ool") {
            "subbing ool".print();
            String tpp = "homeassistant/switch/" + hd.ondid + "-" + i;
            ash.smcserver.subscribe(tpp += "/set");
          } elseIf (hd.met.begins("ecl")) {
            "subbing ecl".print();
            tpp = "homeassistant/light/" + hd.ondid + "-" + i;
            ash.smcserver.subscribe(tpp += "/set");
          }
        }
      }
    }

  }

  pubDevices() {
    if (def(hds)) {
      Int hdslen = hds.length;
      for (Int i = 0;i < hdslen;i++) {
        if (i >= 15) {
          break;
        }
        Hqd hd = hds[i];
        if (def(hd)) {
          if (hd.met == "ool") {
            "pubbing ool".print();
            String uid = hd.ondid + "-" + hd.ipos;
            String tpp = "homeassistant/switch/" + hd.ondid + "-" + i;
            String cfs = "{\"name\":\"Switch\",\"command_topic\":\"" += tpp += "/set\",\"state_topic\":\"" += tpp += "/state\",\"unique_id\":\"" += uid += "\"}";
            ash.smcserver.publish(tpp + "/config", cfs);
            nextPubState = ash.nowup + 200;
          } elseIf (hd.met.begins("ecl")) {
            "pubbing ecl".print();
            uid = hd.ondid + "-" + hd.ipos;
            tpp = "homeassistant/light/" + hd.ondid + "-" + i;
            //cfs = "{\"name\":\"Light\",\"command_topic\":\"" += tpp += "/set\",\"state_topic\":\"" += tpp += "/state\",\"unique_id\":\"" += uid += "\",\"schema\":\"json\",\"brightness\":true,\"supported_color_modes\": [\"rgb\",\"color_temp\"]}";
            cfs = "{\"name\":\"Light\",\"command_topic\":\"" += tpp += "/set\",\"state_topic\":\"" += tpp += "/state\",\"unique_id\":\"" += uid += "\",\"schema\":\"json\",\"brightness\":true,\"supported_color_modes\": [\"hs\",\"color_temp\"]}";
            ash.smcserver.publish(tpp + "/config", cfs);
            nextPubState = ash.nowup + 200;
          }
        }
      }
    }
  }

  saveHds() {
    if (hds.isEmpty) {
      "empty hds".print();
      config.put(hdi, "");
    } else {
      String mc = String.new();
      for (Hqd hd in hds) {
        if (TS.notEmpty(mc)) {
          mc += ".";
        }
        mc += hd.met += "," += hd.ondid += "," += hd.ipos += "," += hd.spass;
      }
      ("conf putting mc " + mc).print();
      config.put(hdi, mc);
    }
  }

  loadHds() {
    String mcs = config.get(hdi);
    if (TS.notEmpty(mcs)) {
      var mce = mcs.split(".");
      for (String mc in mce) {
        var mcl = mc.split(",");
        hds += Hqd.new(mcl[0], mcl[1], mcl[2], mcl[3]);
        ("added Hqd " + mc).print();
      }
    }
  }

  //String cmds = "dostate spass " + ipos + " setsw " + state + " e";
  //also need kdname/ondid
  //so, need this:
  //matrtype,ondid,spass,ipos
  //also, is it add, remove, or clear

  clearHds() {
    config.put(hdi, "");
  }

  start() {

    hdi = config.getPos("hqb.hds");
    "loading hds".print();
    loadHds();

    Int hdslen = hds.length;

    if (hdslen <= 0) { Int ivdiv = 1; } else { ivdiv = hdslen; }
    slots {
      Int swCheckIv = 30000 / ivdiv;//millis per each check on any given device 30000 30 secs, 120000 2 mins, 1800000 30 mins, 600000 10 mins, 360000 6 mins
      Int nextSwCheck = ash.nowup + swCheckIv;
      Int nextSwCheckIdx = 0;
      Int swCycle = 0;//name checks but every 6 cycles get sw (3 mins)
    }

    Embedded:Tds tdserver = ash.tdserver;
    if (def(tdserver)) {
      tdserver.callback = self;
    }

  }

  doSec(String sp) String {
    String iv = System:Random.getString(8);
    String sec = ash.hashIt(iv + "," + sp);
    return(iv + " " + sec);
  }

  sendCmd(Hqd hd, String scmds) String {
      String mcmdres;
      String kdn = "CasNic" + hd.ondid;
      ("checkDoMes kdn scmds |" + kdn + "| |" + scmds + "|").print();
      ifNotEmit(noTds) {
      Embedded:Tds tdserver = ash.tdserver;
      if (def(tdserver)) {
        if (kdn == ash.myName) {
          //"call is coming from inside house".print();
          "selfgate".print();
          //mcmdres = doCmd("matr", scmds);
        } else {
          if (TS.notEmpty(hd.rip)) {
            rip = hd.rip;
          } else {
            String rip = tdserver.getAddrDis(kdn);
          }
          if (rip != CNS.undefined) {
            ("rip " + rip).print();
            hd.rip = rip;
            //look for r and n, send back r n (it's already there) FALSE NOT FROM MQ IT ISN'T
            //String ppay = preq.checkGetPayload(readBuf, slashn);
            var tcpc = Embedded:TCPClient.new(rip, 6420);
            //"open".print();
            tcpc.open();
            //"write".print();
            if (tcpc.connected) {
              tcpc.write(scmds);
              tcpc.write(slashr);
              tcpc.write(slashn);
              //"get tcpcres".print();
              String tcpcres = tcpc.checkGetPayload(readBuf, slashn);
              //"got res".print();
            }
            if (TS.isEmpty(tcpcres)) {
              //"tcpcres empty".print();
              //in case ip changed rewantit
              //hd.rip = null;
              tdserver.sayWants(kdn);
            } else {
              //("tcpcres " + tcpcres).print();
              mcmdres = tcpcres;
            }
          } else {
            "still no rip".print();
          }
        }
      }
    }
    return(mcmdres);
  }

  gotAddr(String name, String rip) {
    if (TS.notEmpty(name) && TS.notEmpty(rip)) {
      String did = name.substring(6, name.length);
      //("did in gotwants " + name + " " + did).print();
      for (Hqd hd in hds) {
        if (TS.notEmpty(hd.ondid)) {
          if (hd.ondid == did) {
            hd.rip = rip;
            //"equal".print();
            break;
          } else {
            //"not equal".print();
          }
        }
      }
    }
  }

  handleLoop() {
    unless(checkPubStates()) {
      devCheck();
    }
  }

  devCheck() {
      if (ash.nowup > nextSwCheck) {
        nextSwCheck = ash.nowup + swCheckIv;
        if (nextSwCheckIdx >= hds.length) {
          nextSwCheckIdx = 0;
          swCycle++;
          if (swCycle > 5) { swCycle = 0; }
        }
        //("doing getsw for mep " + nextSwCheckIdx).print();
        Hqd mmep = hds.get(nextSwCheckIdx);
        if (def(mmep)) {
          if (swCycle == 5) {
            //kdn = "CasNic" + mmep.ondid;
            String scmds = "sp2 " + doSec(mmep.spass) + " dostate X " + mmep.ipos + " getsw e";
            String res = sendCmd(mmep, scmds);
            if (TS.notEmpty(res)) {
              //("got res |" + res + "|").print();
              if (res.has(CNS.on)) {
                Bool swto = true;
              } elseIf (res.has(CNS.off)) {
                swto = false;
              }
              if (def(swto)) {
                mmep.sw = swto;
              }
            } else {
              //"res was empty".print();
            }
          } else {
            if (TS.isEmpty(mmep.rip)) {
              Embedded:Tds tdserver = ash.tdserver;
              if (def(tdserver)) {
                String kdn = "CasNic" + mmep.ondid;
                String rip = tdserver.getAddrDis(kdn);
                if (rip != CNS.undefined) {
                  mmep.rip = rip;
                }
              }
            }
          }
        }
        nextSwCheckIdx++;
        return(true);
      }
      return(false);
    }

}
