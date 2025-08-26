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
      if (top.begins("homeassistant/switch/") && top.ends("/set")) {
        var ll = top.split("/");
        String didpos = ll[2];
        var dp = didpos.split("-");
        Int hdi = Int.new(dp[1]);
        if (def(hds)) {
          Hqd hd = hds[hdi];
          if (def(hd)) {
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
              "not pubbing ecl".print();
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
            "not pubbing ecl".print();
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
            "not pubbing ecl".print();
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

  checkDoMes() {
    //for sw
    Int idx;
    Int st;
    //for dl
    Int bidx;
    Int bb;
    //for ecl
    Int eidx;
    Int est;//sw
    Int ebb;//bright
    Int ebv;//v from hsv
    Int ewt;//temp
    Int er;//color
    Int eg;
    Int eb;
    Int eh;
    Int es;
    Int ev;
    //did I act
    Int didact;

    if (def(idx) && def(st)) {
      didact = 0;
      ("idx " + idx + " st " + st).print();
      Hqd hd = hds.get(idx);
      if (st == 1) {
        String sts = CNS.on;
        Bool tost = true;
      } else {
        sts = CNS.off;
        tost = false;
      }
      if (def(hd)) {
        if (undef(hd.sw) || hd.sw != tost) {
          //String kdn = "CasNic" + hd.ondid;
          //String scmds = "dostate " + hd.spass + " " + hd.ipos + " setsw " + sts + " e";
          //String scres = sendCmd(kdn, scmds);
          String scmds = "sp2 " + doSec(hd.spass) + " dostate X " + hd.ipos + " setsw " + sts + " e";
          String scres = sendCmd(hd, scmds);
          if (TS.notEmpty(scres)) {
            ("scres " + scres).print();
            if (scres.has(CNS.ok)) {
              ("setting hd.sw").print();
              hd.sw = tost;
            }
          }
        } else {
          ("state already " + tost + " not sending dostate").print();
        }
      }
    }
    if (def(bidx) && def(bb)) {
      didact = 1;
      ("bidx " + bidx + " bb " + bb).print();
      hd = hds.get(bidx);
      if (def(hd) && bb > 0) {
         //kdn = "CasNic" + hd.ondid;
         scmds = "sp2 " + doSec(hd.spass) + " dostate X " + hd.ipos + " setlvl " + bb + " e";
         sendCmd(hd, scmds);
      }
    }
    if (def(eidx) && def(est) && def(ebb) && def(ewt) && def(er) && def(eg) && def(eb)) {
      didact = 1;
      hd = hds.get(eidx);
      if (est == 1) {
        String ests = CNS.on;
        Bool etost = true;
      } else {
        ests = CNS.off;
        etost = false;
      }
      if (def(hd)) {
        ("eidx " + eidx + " est " + est + " ebb " + ebb + " ewt " + ewt + " er " + er + " eg " + eg + " eb " + eb).print();
        //kdn = "CasNic" + hd.ondid;
        //scmds = "dostate " + hd.spass + " " + hd.ipos + " setlvl " + bb + " e";
        //sendCmd(kdn, scmds);
        if (def(hd.h) && def(hd.s)) {
          if (def(hd.inCtCh) && hd.inCtCh && hd.h == eh && hd.s == es) {
            //not real hsv changes, just bright reflected in v
            //if already in ctCh stay
            Bool ctCh = true;
            Bool rgbCh = false;
          } elseIf (hd.h == eh && hd.s == es && hd.ct != ewt) {
            ctCh = true;
            rgbCh = false;
          } else {
            ctCh = false;
            rgbCh = true;
          }
          ("ecl on changes ctCh " + ctCh + " rgbCh " + rgbCh).print();
        } else {
          ("ecl first time").print();
          //maybe check values to guess
          rgbCh = true;
          ctCh = false;
          Bool eclFirst = true;
        }
        if (etost) {
          if (rgbCh) {
            if (ebv == 0) { ebv = 255; }
            String rgblct = "" += er += "," += eg += "," += eb += "," += ebv += ",0";//last 0 is cw for rgb case
            ("ecl will dostate rgbCh").print();

            String xd = "" += er += "," += eg += "," += eb += "," += ebv += ",0";
            scmds = "sp2 " + doSec(hd.spass) + " dostatexd X " + hd.ipos + " setrgbcw " + rgblct + " " + xd + " " + " e";
          } elseIf (ctCh) {
            ("ecl will dostate ctCh").print();

            if (ebb == 0) {
              if (def(hd.ctLvl)) { ebb = hd.ctLvl; }
              else { ebb = 255; }
            }

            hd.ctLvl = ebb;
            Int lvli = ebb;
            Int cwi = ewt;
            if (lvli < 0 || lvli > 255) { lvli = 255; }
            if (lvli == 1) { lvli = 2; } //cws seems to be off at analog write 1
            if (cwi < 0 || cwi > 255) { cwi = 255; }
            cwi = 255 - cwi;

            rgblct = "255,255,255," += ebb; //,cw
            xd = "255,255,255," += ebb; //,cw

            xd += "," += ewt;
            rgblct += "," += cwi;

            scmds = "sp2 " + doSec(hd.spass) + " dostatexd X " + hd.ipos + " setrgbcw " + rgblct + " " + xd + " " + " e";
          }
          if (TS.notEmpty(scmds)) {
            //kdn = "CasNic" + hd.ondid;
            scres = sendCmd(hd, scmds);
            //if fails set etost to false
            unless (TS.notEmpty(scres) && scres.has(CNS.ok)) {
              "attempt failed setting etost false".print();
              //if fails set etost to false
              etost = false;
            }
          }
        } else {
          //it's off, that's all
          //capture vals, they are set after off to recover original state after a "transition"
          //turn it off
          unless (def(eclFirst) && eclFirst) {
            ("ecl will dostate sw off").print();
            //kdn = "CasNic" + hd.ondid;
            scmds = "sp2 " + doSec(hd.spass) + " dostate X " + hd.ipos + " setsw " + ests + " e";
            scres = sendCmd(hd, scmds);
            unless (TS.notEmpty(scres) && scres.has(CNS.ok)) {
              "attempt failed setting etost true".print();
              //if fails set etost to true
              etost = true;
            }
          }
        }
        if (ctCh) {
          hd.inCtCh = true;
        }
        if (rgbCh) {
          hd.inCtCh = false;
        }
        hd.sw = etost;
        hd.ct = ewt;
        hd.h = eh;
        hd.s = es;
        hd.v = ev;
      }
    }
    if (undef(didact)) {
      if (ash.nowup > nextSwCheck) {
        nextSwCheck = ash.nowup + swCheckIv;
        if (nextSwCheckIdx >= hds.length) {
          nextSwCheckIdx = 0;
        }
        //("doing getsw for mep " + nextSwCheckIdx).print();
        hd = hds.get(nextSwCheckIdx);
        if (def(hd)) {
          //kdn = "CasNic" + hd.ondid;
          scmds = "sp2 " + doSec(hd.spass) + " dostate X " + hd.ipos + " getsw e";
          String res = sendCmd(hd, scmds);
          if (TS.notEmpty(res)) {
            //("got res |" + res + "|").print();
            if (res.has(CNS.on)) {
              Bool swto = true;
            } elseIf (res.has(CNS.off)) {
              swto = false;
            }
            if (hd.met == "ool") {
              Int hdmet = 0;
            } elseIf (hd.met == "dl") {
              hdmet = 1;
            } elseIf (hd.met == "ecl") {
              hdmet = 2;
            }
            if (def(swto)) {
              hd.sw = swto;
              //"doing sloo".print();
            }
          } else {
            //"res was empty".print();
          }
        }
        nextSwCheckIdx++;
      }
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
    //checkDoMes();
    checkPubStates();
  }

}
