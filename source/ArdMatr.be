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

//
//https://github.com/espressif/arduino-esp32/blob/master/libraries/Matter/examples/MatterOnOffLight/MatterOnOffLight.ino
//put in BEAR_Imports.hpp for esp32
//#include <Matter.h>
//
//looks like max 15 devices/endpoints supported at present

use Embedded:CommonNames as CNS;
use Embedded:Mmep;

emit(cc) {
  """

  using sloocb = std::function<bool(bool)>;
  using sdlscb = std::function<bool(bool,uint8_t)>;
  using seclscb = std::function<bool(bool, espHsvColor_t, uint8_t, uint16_t)>;

  std::mutex cmdsLk;
  std::deque<int> cmdsDq;
  std::deque<bool> stateDq;
  std::deque<uint8_t> brightDq;
  std::deque<uint16_t> tempDq;
  std::deque<espHsvColor_t> hsvDq;

  bool setLightOnOff(size_t idx, bool state) {
    Serial.printf("setLightOnOff %zu changed state to: %d\r\n", idx, state);
    cmdsLk.lock();
    try {
      cmdsDq.push_front(0);
      cmdsDq.push_front(idx);
      stateDq.push_front(state);
    } catch (...) {
      cmdsLk.unlock();
    }
    cmdsLk.unlock();
    return true;
  }
  bool sloo0(bool state) { return setLightOnOff(0, state); }
  bool sloo1(bool state) { return setLightOnOff(1, state); }
  bool sloo2(bool state) { return setLightOnOff(2, state); }
  bool sloo3(bool state) { return setLightOnOff(3, state); }
  bool sloo4(bool state) { return setLightOnOff(4, state); }
  bool sloo5(bool state) { return setLightOnOff(5, state); }
  bool sloo6(bool state) { return setLightOnOff(6, state); }
  bool sloo7(bool state) { return setLightOnOff(7, state); }
  bool sloo8(bool state) { return setLightOnOff(8, state); }
  bool sloo9(bool state) { return setLightOnOff(9, state); }
  bool sloo10(bool state) { return setLightOnOff(10, state); }
  bool sloo11(bool state) { return setLightOnOff(11, state); }
  bool sloo12(bool state) { return setLightOnOff(12, state); }
  bool sloo13(bool state) { return setLightOnOff(13, state); }
  bool sloo14(bool state) { return setLightOnOff(14, state); }

  std::vector<sloocb> sloocbs = { sloo0, sloo1, sloo2, sloo3, sloo4, sloo5, sloo6, sloo7, sloo8, sloo9, sloo10, sloo11, sloo12, sloo13, sloo14 };

  bool setDimLightState(size_t idx, bool state, uint8_t brightness) {
    Serial.printf("setDimLightState %zu changed state to: %d %u\r\n", idx, state, brightness);
    cmdsLk.lock();
    try {
      if (state) {
        cmdsDq.push_front(1);
        cmdsDq.push_front(idx);
        brightDq.push_front(brightness);
      } else {
        cmdsDq.push_front(0);
        cmdsDq.push_front(idx);
        stateDq.push_front(state);
      }
    } catch (...) {
      cmdsLk.unlock();
    }
    cmdsLk.unlock();
    return true;
  }

  bool sdls0(bool state, uint8_t brightness) { return setDimLightState(0, state, brightness); }
  bool sdls1(bool state, uint8_t brightness) { return setDimLightState(1, state, brightness); }
  bool sdls2(bool state, uint8_t brightness) { return setDimLightState(2, state, brightness); }
  bool sdls3(bool state, uint8_t brightness) { return setDimLightState(3, state, brightness); }
  bool sdls4(bool state, uint8_t brightness) { return setDimLightState(4, state, brightness); }
  bool sdls5(bool state, uint8_t brightness) { return setDimLightState(5, state, brightness); }
  bool sdls6(bool state, uint8_t brightness) { return setDimLightState(6, state, brightness); }
  bool sdls7(bool state, uint8_t brightness) { return setDimLightState(7, state, brightness); }
  bool sdls8(bool state, uint8_t brightness) { return setDimLightState(8, state, brightness); }
  bool sdls9(bool state, uint8_t brightness) { return setDimLightState(9, state, brightness); }
  bool sdls10(bool state, uint8_t brightness) { return setDimLightState(10, state, brightness); }
  bool sdls11(bool state, uint8_t brightness) { return setDimLightState(11, state, brightness); }
  bool sdls12(bool state, uint8_t brightness) { return setDimLightState(12, state, brightness); }
  bool sdls13(bool state, uint8_t brightness) { return setDimLightState(13, state, brightness); }
  bool sdls14(bool state, uint8_t brightness) { return setDimLightState(14, state, brightness); }

  std::vector<sdlscb> sdlscbs = { sdls0, sdls1, sdls2, sdls3, sdls4, sdls5, sdls6, sdls7, sdls8, sdls9, sdls10, sdls11, sdls12, sdls13, sdls14 };

  bool setECLState(size_t idx, bool state, espHsvColor_t color, uint8_t brightness, uint16_t witemp) {
    Serial.printf("setECLState %zu changed to: state %d bright %u temp %u\r\n", idx, state, brightness, witemp);
    Serial.printf("hsv %u %u %u\r\n", color.h, color.s, color.v);
    cmdsLk.lock();
    try {
      cmdsDq.push_front(2);
      cmdsDq.push_front(idx);
      stateDq.push_front(state);
      brightDq.push_front(brightness);
      tempDq.push_front(witemp);
      hsvDq.push_front(color);
    } catch (...) {
      cmdsLk.unlock();
    }
    cmdsLk.unlock();
    return true;
  }

  //std::function<bool(bool, espHsvColor_t, uint8_t, uint16_t)>;
  bool secls0(bool state, espHsvColor_t color, uint8_t brightness, uint16_t witemp) { return setECLState(0, state, color, brightness, witemp); }
  bool secls1(bool state, espHsvColor_t color, uint8_t brightness, uint16_t witemp) { return setECLState(1, state, color, brightness, witemp); }
  bool secls2(bool state, espHsvColor_t color, uint8_t brightness, uint16_t witemp) { return setECLState(2, state, color, brightness, witemp); }
  bool secls3(bool state, espHsvColor_t color, uint8_t brightness, uint16_t witemp) { return setECLState(3, state, color, brightness, witemp); }
  bool secls4(bool state, espHsvColor_t color, uint8_t brightness, uint16_t witemp) { return setECLState(4, state, color, brightness, witemp); }

  std::vector<seclscb> seclscbs = { secls0, secls1, secls2, secls3, secls4 };

  """
}

class Embedded:MatrServer {

emit(cc_classHead) {
"""
std::vector<std::shared_ptr<MatterEndPoint>> bevi_meps;
"""
}

  new(_ash) self {
    slots {
      Embedded:AppShell ash = _ash;
      Config config = ash.config;
      Int mepi;
      List meps = List.new();
      String slashn = "\n";
      String slashr = "\r";
      String readBuf = String.new();
      Bool triedCommission = false;
      Bool brdCh = false;
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
          clearMeps();
          //ash.needsFsRestart = true;
        } elseIf (cmdl.length > 2 && cmdl[2] == "commish") {
          commission();
        } elseIf (cmdl.length > 2 && cmdl[2] == "decommish") {
          timeToDecom = true;
        } elseIf (cmdl.length > 2 && cmdl[2] == "rmold") {
          nx = List.new();
          nowup = ash.nowup;
          if (def(nowup)) {
            for (mmep in meps) {
              //mmep.lastUp = nowup;
              if (undef(mmep.lastUp) || nowup - mmep.lastUp > 60000) {
                "rmold removing a device".print();
                brdCh = true;
              } else {
                 nx += mmep;
              }
            }
          }
          meps = nx;
          saveMeps();
        } elseIf (cmdl.length > 2 && cmdl[2] == "chrestart") {
          if (brdCh) {
            "will restart chrestart".print();
            brdCh = false;
            ash.needsFsRestart = true;
          }
        } elseIf (cmdl.length > 3) {
          Int nowup = ash.nowup;
          String act = cmdl[2];
          if (act == "add" && cmdl.length > 6) {
            if (meps.length >= 15) {
              return("brdtoomany");
            }
            for (Mmep mmep in meps) {
              if (mmep.ondid == cmdl[4] && mmep.ipos == cmdl[5]) {
                "brd add sent a dupe".print();
                mmep.lastUp = nowup;
                return("brdok");
              }
            }
            brdCh = true;
            Mmep addm = Mmep.new(cmdl[3], cmdl[4], cmdl[5], cmdl[6]);
            addm.lastUp = nowup;
            meps += addm;
            saveMeps();
            //ash.needsFsRestart = true;
          } elseIf (act == "rm" && cmdl.length > 5) {
            List nx = List.new();
            for (mmep in meps) {
              if (mmep.ondid == cmdl[4] && mmep.ipos == cmdl[5]) {
                brdCh = true;
              } else {
                nx += mmep;
              }
            }
            meps = nx;
            saveMeps();
            //ash.needsFsRestart = true;
          } else {
            ("unknown matr act " + act).print();
            return("brdbadact");
          }
        } else {
          "bad brd cmd".print();
          return("brdbadcmd");
        }
        return("brdok");
  }

  saveMeps() {
    if (meps.isEmpty) {
      "empty meps".print();
      config.put(mepi, "");
    } else {
      String mc = String.new();
      for (Mmep mmep in meps) {
        if (TS.notEmpty(mc)) {
          mc += ".";
        }
        mc += mmep.met += "," += mmep.ondid += "," += mmep.ipos += "," += mmep.spass;
      }
      ("conf putting mc " + mc).print();
      config.put(mepi, mc);
    }
  }

  loadMeps() {
    String mcs = config.get(mepi);
    if (TS.notEmpty(mcs)) {
      var mce = mcs.split(".");
      for (String mc in mce) {
        var mcl = mc.split(",");
        meps += Mmep.new(mcl[0], mcl[1], mcl[2], mcl[3]);
        ("added Mmep " + mc).print();
      }
    }
  }

  //String cmds = "dostate spass " + ipos + " setsw " + state + " e";
  //also need kdname/ondid
  //so, need this:
  //matrtype,ondid,spass,ipos
  //also, is it add, remove, or clear

  clearMeps() {
    config.put(mepi, "");
  }

  gotAddr(String name, String rip) {
    if (TS.notEmpty(name) && TS.notEmpty(rip)) {
      String did = name.substring(6, name.length);
      //("did in gotwants " + name + " " + did).print();
      for (Mmep mmep in meps) {
        if (TS.notEmpty(mmep.ondid)) {
          if (mmep.ondid == did) {
            mmep.rip = rip;
            //"equal".print();
            break;
          } else {
            //"not equal".print();
          }
        }
      }
    }
  }

  start() {

    ifNotEmit(noTds) {
      Embedded:Tds tdserver = ash.tdserver;
      if (def(tdserver)) {
        tdserver.callback = self;
      }
    }

    mepi = config.getPos("matr.meps");
    "loading meps".print();
    loadMeps();

    Int mepslen = meps.length;

    for (Int i = 0;i < mepslen;i++) {
      if (i >= 15) {
        break;
      }
      Mmep mmep = meps[i];
      if (def(mmep)) {
        Int meti;
        if (mmep.met == "ool") {
          meti = 0;
        } elseIf (mmep.met == "dl") {
          meti = 1;
        } elseIf (mmep.met.begins("ecl")) {
          meti = 2;
        }
        if (def(meti)) {
          emit(cc) {
            """
            int meti = beq->bevl_meti->bevi_int;
            int mepi = beq->bevl_i->bevi_int;
            if (meti == 0) {
              std::shared_ptr<MatterOnOffLight> bevi_mool;
              bevi_mool = std::make_shared<MatterOnOffLight>();
              bevi_mool->begin();
              bevi_mool->onChangeOnOff(sloocbs[mepi]);
              bevi_meps.push_back(bevi_mool);
            }
            if (meti == 1) {
              std::shared_ptr<MatterDimmableLight> bevi_mdl;
              bevi_mdl = std::make_shared<MatterDimmableLight>();
              bevi_mdl->begin();
              bevi_mdl->onChange(sdlscbs[mepi]);
              bevi_meps.push_back(bevi_mdl);
            }
            if (meti == 2) {
              std::shared_ptr<MatterEnhancedColorLight> bevi_mecl;
              bevi_mecl = std::make_shared<MatterEnhancedColorLight>();
              bevi_mecl->begin();
              bevi_mecl->onChange(seclscbs[mepi]);
              bevi_meps.push_back(bevi_mecl);
            }
            """
          }
        }
      }
    }

    emit(cc) {
      """
      int ml = beq->bevl_mepslen->bevi_int;
      if (ml < 1) {
        //must have one to avoid decommissioning
        std::shared_ptr<MatterOnOffLight> bevi_mool;
        bevi_mool = std::make_shared<MatterOnOffLight>();
        bevi_mool->begin();
        bevi_mool->onChangeOnOff(sloocbs[0]);
        bevi_meps.push_back(bevi_mool);
      }
      Matter.begin();
      """
    }

    if (mepslen <= 0) { Int ivdiv = 1; } else { ivdiv = mepslen; }
    slots {
      Int swCheckIv = 30000 / ivdiv;//millis per each check on any given device 30000 30 secs, 120000 2 mins, 1800000 30 mins, 600000 10 mins, 360000 6 mins
      Int nextSwCheck = ash.nowup + swCheckIv;
      Int nextSwCheckIdx = 0;
      Int swCycle = 0;//name checks but every 6 cycles get sw (3 mins)
    }

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
    emit(cc) {
      """
      int act = -1;
      int idx = -1;
      bool state = false;
      uint8_t bright;
      uint16_t ewt;
      espHsvColor_t hsv;

      cmdsLk.lock();
      try {
        if (!cmdsDq.empty()) {
          act = cmdsDq.back();
          cmdsDq.pop_back();
          idx = cmdsDq.back();
          cmdsDq.pop_back();
          if (act == 0) {
            state = stateDq.back();
            stateDq.pop_back();
          } else if (act == 1) {
            bright = brightDq.back();
            brightDq.pop_back();
          } else if (act == 2) {
            state = stateDq.back();
            stateDq.pop_back();
            bright = brightDq.back();
            brightDq.pop_back();
            ewt = tempDq.back();
            tempDq.pop_back();
            hsv = hsvDq.back();
            hsvDq.pop_back();
            //Serial.printf("checkDoMes %zu changed to: state %d bright %u temp %u\r\n", idx, state, bright, ewt);
          }
        }
      } catch (...) {
        cmdsLk.unlock();
      }
      cmdsLk.unlock();

      if (act == 0) {
        beq->bevl_idx = new BEC_2_4_3_MathInt(idx);
        if (state) {
          beq->bevl_st = new BEC_2_4_3_MathInt(1);
        } else {
          beq->bevl_st = new BEC_2_4_3_MathInt(0);
        }
      }

      if (act == 1) {
        beq->bevl_bidx = new BEC_2_4_3_MathInt(idx);
        beq->bevl_bb = new BEC_2_4_3_MathInt(bright);
      }

      if (act == 2) {
        beq->bevl_eidx = new BEC_2_4_3_MathInt(idx);
        if (state) {
          beq->bevl_est = new BEC_2_4_3_MathInt(1);
        } else {
          beq->bevl_est = new BEC_2_4_3_MathInt(0);
        }
        beq->bevl_ebb = new BEC_2_4_3_MathInt(bright);

        Serial.printf("ewt1 %d\r\n", ewt);

        //if (ewt >= 100) { ewt = ewt - 100; }
        ewt = ewt + 200;
        if (ewt >= 800) { ewt = 800; }

        float tff = 800;
        float ef = (float)((int) ewt);
        float mul = ef / tff;
        Serial.printf("mul %f\r\n", mul);
        float ns = 255;
        ef = mul * ns;
        ewt = (int) ef;
        Serial.printf("ewt2 %d\r\n", ewt);

        beq->bevl_ewt = new BEC_2_4_3_MathInt(ewt);

        beq->bevl_eh = new BEC_2_4_3_MathInt(hsv.h);
        beq->bevl_es = new BEC_2_4_3_MathInt(hsv.s);
        beq->bevl_ev = new BEC_2_4_3_MathInt(hsv.v);

        if (bright != 0) {
          hsv.v = bright;
          beq->bevl_ebv = new BEC_2_4_3_MathInt(bright);
        } else {
          beq->bevl_ebv = new BEC_2_4_3_MathInt(hsv.v);
        }
        espRgbColor_t rgb = espHsvColorToRgbColor(hsv);

        beq->bevl_er = new BEC_2_4_3_MathInt(rgb.r);
        beq->bevl_eg = new BEC_2_4_3_MathInt(rgb.g);
        beq->bevl_eb = new BEC_2_4_3_MathInt(rgb.b);

      }
      """
    }
    if (def(idx) && def(st)) {
      didact = 0;
      ("idx " + idx + " st " + st).print();
      Mmep mmep = meps.get(idx);
      if (st == 1) {
        String sts = CNS.on;
        Bool tost = true;
      } else {
        sts = CNS.off;
        tost = false;
      }
      if (def(mmep)) {
        //if (undef(mmep.sw) || mmep.sw != tost) {
          //String kdn = "CasNic" + mmep.ondid;
          //String scmds = "dostate " + mmep.spass + " " + mmep.ipos + " setsw " + sts + " e";
          //String scres = sendCmd(kdn, scmds);
          String scmds = "sp2 " + doSec(mmep.spass) + " dostate X " + mmep.ipos + " setsw " + sts + " e";
          String scres = sendCmd(mmep, scmds);
          if (TS.notEmpty(scres)) {
            ("scres " + scres).print();
            if (scres.has(CNS.ok)) {
              ("setting mmep.sw").print();
              mmep.sw = tost;
            }
          }
        //} else {
        //  ("state already " + tost + " not sending dostate").print();
        //}
      }
    }
    if (def(bidx) && def(bb)) {
      didact = 1;
      ("bidx " + bidx + " bb " + bb).print();
      mmep = meps.get(bidx);
      if (def(mmep) && bb > 0) {
         //kdn = "CasNic" + mmep.ondid;
         scmds = "sp2 " + doSec(mmep.spass) + " dostate X " + mmep.ipos + " setlvl " + bb + " e";
         sendCmd(mmep, scmds);
      }
    }
    if (def(eidx) && def(est) && def(ebb) && def(ewt) && def(er) && def(eg) && def(eb)) {
      didact = 1;
      mmep = meps.get(eidx);
      if (est == 1) {
        String ests = CNS.on;
        Bool etost = true;
      } else {
        ests = CNS.off;
        etost = false;
      }
      if (def(mmep)) {
        ("eidx " + eidx + " est " + est + " ebb " + ebb + " ewt " + ewt + " er " + er + " eg " + eg + " eb " + eb).print();
        //kdn = "CasNic" + mmep.ondid;
        //scmds = "dostate " + mmep.spass + " " + mmep.ipos + " setlvl " + bb + " e";
        //sendCmd(kdn, scmds);
        if (def(mmep.h) && def(mmep.s)) {
          if (def(mmep.inCtCh) && mmep.inCtCh && mmep.h == eh && mmep.s == es) {
            //not real hsv changes, just bright reflected in v
            //if already in ctCh stay
            Bool ctCh = true;
            Bool rgbCh = false;
          } elseIf (mmep.h == eh && mmep.s == es && mmep.ct != ewt) {
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
            scmds = "sp2 " + doSec(mmep.spass) + " dostatexd X " + mmep.ipos + " setrgbcw " + rgblct + " " + xd + " " + " e";
          } elseIf (ctCh) {
            ("ecl will dostate ctCh").print();

            if (ebb == 0) {
              if (def(mmep.ctLvl)) { ebb = mmep.ctLvl; }
              else { ebb = 255; }
            }

            mmep.ctLvl = ebb;

            xd = "255,255,255," += ebb; //,cw
            xd += "," += ewt;

            if (mmep.met == "ecl") {
              rgblct = "255,255,255," += cwForCwsLvl(ewt, ebb);
            } elseIf (mmep.met == "eclns") {
              rgblct = "255,255,255," += cwForCwLvl(ewt, ebb);
            }

            scmds = "sp2 " + doSec(mmep.spass) + " dostatexd X " + mmep.ipos + " setrgbcw " + rgblct + " " + xd + " " + " e";
          }
          if (TS.notEmpty(scmds)) {
            //kdn = "CasNic" + mmep.ondid;
            scres = sendCmd(mmep, scmds);
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
            //kdn = "CasNic" + mmep.ondid;
            scmds = "sp2 " + doSec(mmep.spass) + " dostate X " + mmep.ipos + " setsw " + ests + " e";
            scres = sendCmd(mmep, scmds);
            unless (TS.notEmpty(scres) && scres.has(CNS.ok)) {
              "attempt failed setting etost true".print();
              //if fails set etost to true
              etost = true;
            }
          }
        }
        if (ctCh) {
          mmep.inCtCh = true;
        }
        if (rgbCh) {
          mmep.inCtCh = false;
        }
        mmep.sw = etost;
        mmep.ct = ewt;
        mmep.h = eh;
        mmep.s = es;
        mmep.v = ev;
      }
    }
    if (undef(didact)) {
      if (ash.nowup > nextSwCheck) {
        nextSwCheck = ash.nowup + swCheckIv;
        if (nextSwCheckIdx >= meps.length) {
          nextSwCheckIdx = 0;
          swCycle++;
          if (swCycle > 5) { swCycle = 0; }
        }
        //("doing getsw for mep " + nextSwCheckIdx).print();
        mmep = meps.get(nextSwCheckIdx);
        if (def(mmep)) {
          if (swCycle == 5) {
            //kdn = "CasNic" + mmep.ondid;
            scmds = "sp2 " + doSec(mmep.spass) + " dostate X " + mmep.ipos + " getsw e";
            String res = sendCmd(mmep, scmds);
            if (TS.notEmpty(res)) {
              //("got res |" + res + "|").print();
              if (res.has(CNS.on)) {
                Bool swto = true;
              } elseIf (res.has(CNS.off)) {
                swto = false;
              }
              if (mmep.met == "ool") {
                Int mmepmet = 0;
              } elseIf (mmep.met == "dl") {
                mmepmet = 1;
              } elseIf (mmep.met.begins("ecl")) {
                mmepmet = 2;
              }
              if (def(swto)) {
                mmep.sw = swto;
                //"doing sloo".print();
                emit(cc) {
                  """
                  bool swtost = beq->bevl_swto->bevi_bool;
                  std::shared_ptr<MatterEndPoint> swmep = bevi_meps[bevp_nextSwCheckIdx->bevi_int];
                  bool didup = false;
                  if (beq->bevl_mmepmet->bevi_int == 0) {
                  std::shared_ptr<MatterOnOffLight> swool = std::static_pointer_cast<MatterOnOffLight>(swmep);
                  if (swool->getOnOff() != swtost) {
                    didup = true;
                    Serial.println("will setonoff");
                    swool->setOnOff(swtost);
                  }
                  }
                  if (beq->bevl_mmepmet->bevi_int == 1) {
                  std::shared_ptr<MatterDimmableLight> swdl = std::static_pointer_cast<MatterDimmableLight>(swmep);
                  if (swdl->getOnOff() != swtost) {
                    didup = true;
                    Serial.println("will setonoff");
                    swdl->setOnOff(swtost);
                  }
                  }
                  if (beq->bevl_mmepmet->bevi_int == 2) {
                  std::shared_ptr<MatterEnhancedColorLight> mecl = std::static_pointer_cast<MatterEnhancedColorLight>(swmep);
                  if (mecl->getOnOff() != swtost) {
                    didup = true;
                    Serial.println("will setonoff");
                    mecl->setOnOff(swtost);
                  }
                  }
                  if (didup) {
                    """
                  }
                  emit(cc) {
                    """
                  }
                  """
                }
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
      }
    }
  }

  doSec(String sp) String {
    String iv = System:Random.getString(8);
    String sec = ash.hashIt(iv + "," + sp);
    return(iv + " " + sec);
  }

  sendCmd(Mmep mmep, String scmds) String {
      String mcmdres;
      String kdn = "CasNic" + mmep.ondid;
      ("checkDoMes kdn scmds |" + kdn + "| |" + scmds + "|").print();
      ifNotEmit(noTds) {
      Embedded:Tds tdserver = ash.tdserver;
      if (def(tdserver)) {
        if (kdn == ash.myName) {
          //"call is coming from inside house".print();
          "selfgate".print();
          //mcmdres = doCmd("matr", scmds);
        } else {
          if (TS.notEmpty(mmep.rip)) {
            rip = mmep.rip;
          } else {
            String rip = tdserver.getAddrDis(kdn);
          }
          if (rip != CNS.undefined) {
            ("rip " + rip).print();
            mmep.rip = rip;
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
              //mmep.rip = null;
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

  handleLoop() {
   checkDoMes();
   unless (triedCommission) {
     triedCommission = true;
     //commission();
   }
   if (timeToDecom) {
     timeToDecom = false;
     "decom".print();
     decommission();
     "decom done".print();
   }
  }

  commission() {
    emit(cc) {
      """
      //Matter.decommission();
      if (!Matter.isDeviceCommissioned()) {
        Serial.println("");
        Serial.println("Matter Node is not commissioned yet.");
        Serial.println("Initiate the device discovery in your Matter environment.");
        Serial.println("Commission it to your Matter hub with the manual pairing code or QR code");
        Serial.printf("Manual pairing code: %s\r\n", Matter.getManualPairingCode().c_str());
        Serial.printf("QR code URL: %s\r\n", Matter.getOnboardingQRCodeUrl().c_str());
        // waits for Matter Light Commissioning.
        uint32_t timeCount = 0;
        while (!Matter.isDeviceCommissioned()) {
          delay(100);
          if ((timeCount++ % 50) == 0) {  // 50*100ms = 5 sec
            Serial.println("Matter Node not commissioned yet. Waiting for commissioning.");
          }
          if (timeCount > 3000) { //5 mins
          //if (timeCount > 300) { //30s, for testing
            Serial.println("Matter Node not commissioned after 5 mins.  Giving up, unplug and replug to get another 5 minute window for commissioning");
            break;
          //}
          }
        }
        if (Matter.isDeviceCommissioned()) {
          Serial.println("Matter Node is commissioned and connected to Wi-Fi. Ready for use.");
        } else {
          Serial.println("Matter was not commissioned.");
        }
      } else {
        Serial.println("Matter Node already provisioned");
      }
      """
    }
  }

  decommission() {
    emit(cc) {
      """
      if (Matter.isDeviceCommissioned()) {
        Matter.decommission();
      }
      """
    }
  }

}
