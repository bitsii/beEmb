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

  std::mutex cmdsLk;
  std::deque<int> cmdsDq;

  bool setLightOnOff(size_t idx, bool state) {
    Serial.printf("setLightOnOff %zu changed state to: %d\r\n", idx, state);
    int sti;
    if (state) {
     sti = 1;
    } else {
     sti = 0;
    }
    cmdsLk.lock();
    try {
      cmdsDq.push_back(0);
      cmdsDq.push_back(idx);
      cmdsDq.push_back(sti);
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
    int act;
    int val;
    if (state) {
     act = 1;
     val = brightness;
    } else {
     act = 0;
     val = 0;
    }
    cmdsLk.lock();
    try {
      cmdsDq.push_back(act);
      cmdsDq.push_back(idx);
      cmdsDq.push_back(val);
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
        } elseIf (cmdl.length > 3) {
          String act = cmdl[2];
          if (act == "add" && cmdl.length > 6) {
            if (meps.length >= 15) {
              return("matreptoomany");
            }
            meps += Mmep.new(cmdl[3], cmdl[4], cmdl[5], cmdl[6]);
            saveMeps();
            //ash.needsFsRestart = true;
          } elseIf (act == "rm" && cmdl.length > 5) {
            List nx = List.new();
            for (Mmep mmep in meps) {
              unless (mmep.ondid == cmdl[4] && mmep.ipos == cmdl[5]) {
                nx += mmep;
              }
            }
            meps = nx;
            saveMeps();
            //ash.needsFsRestart = true;
          } else {
            ("unknown matr act " + act).print();
            return("matrbadact");
          }
        } else {
          "bad matrep cmd".print();
          return("matrepbadcmd");
        }
        return("matrepok");
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

  start() {

    ifNotEmit(noTds) {
      Embedded:Tds tdserver = ash.tdserver;
      if (def(tdserver)) {
        tdserver.mW = 9;
        tdserver.mH = 6;
        /*for (Embedded:Mmep mmep in ools) {
          String kdn = "CasNic" + mmep.ondid;
          tdserver.getAddr(kdn);
          tdserver.update();
        }*/
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
      Int swCheckIv = 36000 / ivdiv;//millis per each check on any given device
      Int nextSwCheck = ash.nowup + swCheckIv;
      Int nextSwCheckIdx = 0;
    }

  }

  checkDoMes() {
    Int idx;
    Int st;
    Int bidx;
    Int bb;
    Int didact;
    slots {
      Int lastSwcIdx;
      String lastSwcState;
    }
    emit(cc) {
      """
      int act = -1;
      int idx = -1;
      int val = -1;

      cmdsLk.lock();
      try {
        if (!cmdsDq.empty()) {
          act = cmdsDq.front();
          cmdsDq.pop_front();
          if (act == 0 || act == 1) {
            idx = cmdsDq.front();
            cmdsDq.pop_front();
            val = cmdsDq.front();
            cmdsDq.pop_front();
          }
        }
      } catch (...) {
        cmdsLk.unlock();
      }
      cmdsLk.unlock();

      if (act == 0) {
        beq->bevl_idx = new BEC_2_4_3_MathInt(idx);
        beq->bevl_st = new BEC_2_4_3_MathInt(val);
      }

      if (act == 1) {
        beq->bevl_bidx = new BEC_2_4_3_MathInt(idx);
        beq->bevl_bb = new BEC_2_4_3_MathInt(val);
      }
      """
    }
    if (def(idx) && def(st)) {
      didact = 0;
      ("idx " + idx + " st " + st).print();
      Mmep mmep = meps.get(idx);
      if (st == 1) {
        String sts = CNS.on;
      } else {
        sts = CNS.off;
      }
      if (def(lastSwcIdx) && idx == lastSwcIdx && def(lastSwcState) && sts == lastSwcState) {
        "not doing update is callthrough".print();
        lastSwcIdx = null;
      } else {
        if (def(mmep)) {
          String kdn = "CasNic" + mmep.ondid;
          String scmds = "dostate " + mmep.spass + " " + mmep.ipos + " setsw " + sts + " e";
          sendCmd(kdn, scmds);
        }
      }
    }
    if (def(bidx) && def(bb)) {
      didact = 1;
      ("bidx " + bidx + " bb " + bb).print();
      mmep = meps.get(bidx);
      if (def(mmep) && bb > 0) {
         kdn = "CasNic" + mmep.ondid;
         scmds = "dostate " + mmep.spass + " " + mmep.ipos + " setlvl " + bb + " e";
         sendCmd(kdn, scmds);
      }
    }
    if (undef(didact)) {
      if (ash.nowup > nextSwCheck) {
        nextSwCheck = ash.nowup + swCheckIv;
        if (nextSwCheckIdx >= meps.length) {
          nextSwCheckIdx = 0;
        }
        //("doing getsw for mep " + nextSwCheckIdx).print();
        mmep = meps.get(nextSwCheckIdx);
        if (def(mmep)) {
          kdn = "CasNic" + mmep.ondid;
          scmds = "dostate " + mmep.spass + " " + mmep.ipos + " getsw e";
          String res = sendCmd(kdn, scmds);
          if (TS.notEmpty(res)) {
            //("got res |" + res + "|").print();
            if (res.has(CNS.on)) {
              Bool swto = true;
              lastSwcState = CNS.on;
            } elseIf (res.has(CNS.off)) {
              swto = false;
              lastSwcState = CNS.off;
            }
            if (mmep.met == "ool") {
              Int mmepmet = 0;
            } elseIf (mmep.met == "dl") {
              mmepmet = 1;
            }
            if (def(swto)) {
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
                if (didup) {
                  """
                }
                lastSwcIdx = nextSwCheckIdx.copy();
                emit(cc) {
                  """
                }
                """
              }
            }
          } else {
            //"res was empty".print();
          }
        }
        nextSwCheckIdx++;
      }
    }
  }

  sendCmd(String kdn, String scmds) String {
      String mcmdres;
      ("checkDoMes kdn scmds |" + kdn + "| |" + scmds + "|").print();
      ifNotEmit(noTds) {
      Embedded:Tds tdserver = ash.tdserver;
      if (def(tdserver)) {
        if (kdn == ash.myName) {
          //"call is coming from inside house".print();
          "selfgate".print();
          //mcmdres = doCmd("matr", scmds);
        } else {
          String rip = tdserver.reallyGetAddr(kdn);
          if (rip != CNS.undefined) {
            ("rip " + rip).print();
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
              tdserver.wants = kdn;
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
     checkGetCommission();
   }
  }

  checkGetCommission() {
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
        Serial.println("Matter Node is commissioned and connected to Wi-Fi. Ready for use.");
      } else {
        //Serial.println("Matter Node already provisioned");
      }
      """
    }
  }

  decommission() {
    emit(cc) {
      """
      Matter.decommission();
      """
    }
  }

}
