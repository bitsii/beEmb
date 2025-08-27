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
        } elseIf (cmdl.length > 3) {
          String act = cmdl[2];
          if (act == "add" && cmdl.length > 6) {
            if (hds.length >= 15) {
              return("brdtoomany");
            }
            for (Hqd hd in hds) {
              if (hd.ondid == cmdl[4] && hd.ipos == cmdl[5]) {
                "brd add sent a dupe".print();
                return("brdok");
              }
            }
            brdCh = true;
            hds += Hqd.new(cmdl[3], cmdl[4], cmdl[5], cmdl[6]);
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
            } elseIf (hd.met == "ecl") {
              "got ecl set".print();
              //do the do. you can tell rgb or temp from what you go, save the mode (rgb or colortemp) on
              //the hd.  will have to use when getting brightness.

              //if it worked send back state.  you need to construct it from the settings, and include brightness, state, color mode, color mode value
              tl = top.split("/");
              stpp = "homeassistant/light/" + tl[2] + "/state";
              ash.smcserver.publish(stpp, msg);
            }
          }
        }
      } elseIf (top == "homeassistant/status" && msg == "online") {
        pubDevices();
      }
    }
  }

  checkPubStates() {
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
            } elseIf (hd.met == "ecl") {
              "pubbing ecl".print();
              uid = hd.ondid + "-" + i;
              tpp = "homeassistant/light/" + uid;
              if (def(hd.sw) && hd.sw) {
                st = "ON";
              } else {
                st = "OFF";
              }
              if (undef(hd.r)) { hd.r = 255; }
              if (undef(hd.g)) { hd.g = 255; }
              if (undef(hd.b)) { hd.b = 255; }
              if (undef(hd.lvl)) { hd.lvl = 255; }
              //String jst = "{\"state\":\"" += st += "\",\"brightness\":" += hd.lvl += ",\"color\":{\"r\":" += hd.r += ",\"g\":" += hd.g += ",\"b\":" += hd.b += "}}";
              String jst = "{\"state\":\"" += st += "\"}";
              ash.smcserver.publish(tpp + "/state", jst);
              //dps.put("brightness", Int.new(lv));
              //dps.put("color_temp", lsToMired(Int.new(cw)));
            }
          }
        }
      }
    }
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
          } elseIf (hd.met == "ecl") {
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
            nextPubState = ash.nowup + 1000;
          } elseIf (hd.met == "ecl") {
            "pubbing ecl".print();
            uid = hd.ondid + "-" + hd.ipos;
            tpp = "homeassistant/light/" + hd.ondid + "-" + i;
            cfs = "{\"name\":\"Light\",\"command_topic\":\"" += tpp += "/set\",\"state_topic\":\"" += tpp += "/state\",\"unique_id\":\"" += uid += "\",\"schema\":\"json\",\"brightness\":true,\"supported_color_modes\": [\"rgb\",\"color_temp\"]}";
            ash.smcserver.publish(tpp + "/config", cfs);
            nextPubState = ash.nowup + 1000;
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
      Int swCheckIv = 360000 / ivdiv;//millis per each check on any given device 30000 30 secs, 120000 2 mins, 1800000 30 mins, 600000 10 mins, 360000 6 mins
      Int nextSwCheck = ash.nowup + swCheckIv;
      Int nextSwCheckIdx = 0;
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
    checkPubStates();
  }

}
