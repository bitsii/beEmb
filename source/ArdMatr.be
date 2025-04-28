/*
 * Copyright (c) 2024-2025, the Beysant Embedded Authors.
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
  using slbcb = std::function<bool(uint8_t)>;

  //have mutex, deque for positions, deque for bools, lock before changing or iterating for changes
  int oolChIdx = -1;
  int oolChSt = -1;
  bool setLightOnOff(size_t idx, bool state) {
    Serial.printf("Light %zu changed state to: %d\r\n", idx, state);
    oolChIdx = idx;
    if (state) {
     oolChSt = 1;
    } else {
     oolChSt = 0;
    }
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

  int lbChIdx = -1;
  int lbChb = -1;
  bool setLightBrightness(size_t idx, uint8_t brightness) {
    Serial.printf("Light %zu changed brightness to: %u\r\n", idx, brightness);
    lbChIdx = idx;
    lbChb = brightness;
    return true;
  }

  bool slb0(uint8_t brightness) { return setLightBrightness(0, brightness); }
  bool slb1(uint8_t brightness) { return setLightBrightness(1, brightness); }
  bool slb2(uint8_t brightness) { return setLightBrightness(2, brightness); }
  bool slb3(uint8_t brightness) { return setLightBrightness(3, brightness); }
  bool slb4(uint8_t brightness) { return setLightBrightness(4, brightness); }
  bool slb5(uint8_t brightness) { return setLightBrightness(5, brightness); }
  bool slb6(uint8_t brightness) { return setLightBrightness(6, brightness); }
  bool slb7(uint8_t brightness) { return setLightBrightness(7, brightness); }
  bool slb8(uint8_t brightness) { return setLightBrightness(8, brightness); }
  bool slb9(uint8_t brightness) { return setLightBrightness(9, brightness); }
  bool slb10(uint8_t brightness) { return setLightBrightness(10, brightness); }
  bool slb11(uint8_t brightness) { return setLightBrightness(11, brightness); }
  bool slb12(uint8_t brightness) { return setLightBrightness(12, brightness); }
  bool slb13(uint8_t brightness) { return setLightBrightness(13, brightness); }
  bool slb14(uint8_t brightness) { return setLightBrightness(14, brightness); }

  std::vector<slbcb> slbcbs = { slb0, slb1, slb2, slb3, slb4, slb5, slb6, slb7, slb8, slb9, slb10, slb11, slb12, slb13, slb14 };
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
    }
  }

  handleCmdl(List cmdl) String {
         //so, need this:
         //act ept ondid ipos spass
         //add ool id ipos spass
         //rm ool id
        if (cmdl.length > 2 && cmdl[2] == "clear") {
          clearMeps();
          ash.needsFsRestart = true;
        } elseIf (cmdl.length > 3) {
          String act = cmdl[2];
          if (act == "add" && cmdl.length > 6) {
            if (meps.length >= 15) {
              return("matreptoomany");
            }
            meps += Mmep.new(cmdl[3], cmdl[4], cmdl[5], cmdl[6]);
            saveMeps();
            ash.needsFsRestart = true;
          } elseIf (act == "rm" && cmdl.length > 5) {
            List nx = List.new();
            for (Mmep mmep in meps) {
              unless (mmep.ondid == cmdl[4] && mmep.ipos == cmdl[5]) {
                nx += mmep;
              }
            }
            meps = nx;
            saveMeps();
            ash.needsFsRestart = true;
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
              bevi_mdl->onChangeOnOff(sloocbs[mepi]);
              bevi_mdl->onChangeBrightness(slbcbs[mepi]);
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
  }

  checkDoMes() {
    Int idx;
    Int st;
    Int bidx;
    Int bb;
    emit(cc) {
      """
      if (oolChIdx >= 0 && oolChSt >= 0) {
        beq->bevl_idx = new BEC_2_4_3_MathInt(oolChIdx);
        beq->bevl_st = new BEC_2_4_3_MathInt(oolChSt);
        oolChIdx = -1;
        oolChSt = -1;
      }
      if (lbChIdx >= 0 && lbChb >= 0) {
        beq->bevl_bidx = new BEC_2_4_3_MathInt(lbChIdx);
        beq->bevl_bb = new BEC_2_4_3_MathInt(lbChb);
        lbChIdx = -1;
        lbChb = -1;
      }
      """
    }
    if (def(idx) && def(st)) {
      ("idx " + idx + " st " + st).print();
      Mmep mmep = meps.get(idx);
      if (st == 1) {
        String sts = "on";
      } else {
        sts = "off";
      }
      if (def(mmep)) {
         String kdn = "CasNic" + mmep.ondid;
         String scmds = "dostate " + mmep.spass + " " + mmep.ipos + " setsw " + sts + " e";
         sendCmd(kdn, scmds);
      }
    }
    if (def(bidx) && def(bb)) {
      ("bidx " + bidx + " bb " + bb).print();
      mmep = meps.get(bidx);
      if (def(mmep) && bb > 1) {  //seems to send 1 after turning off
         kdn = "CasNic" + mmep.ondid;
         scmds = "dostate " + mmep.spass + " " + mmep.ipos + " setlvl " + bb + " e";
         sendCmd(kdn, scmds);
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
   checkGetCommission();
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
