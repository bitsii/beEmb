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
  """
}

class Embedded:MatrServer {

emit(cc_classHead) {
"""
std::vector<std::shared_ptr<MatterOnOffLight>> bevi_mools;
"""
}

  new(_ash) self {
    slots {
      Embedded:AppShell ash = _ash;
      Config config = ash.config;
      Int ooli;
      List ools = List.new();
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
          clearMmeps();
          ash.needsFsRestart = true;
        } elseIf (cmdl.length > 3) {
          String act = cmdl[2];
          String ept = cmdl[3];
          if (act == "add" && ept == "ool" && cmdl.length > 6) {
            ools += Mmep.new(cmdl[4], cmdl[5], cmdl[6]);
            saveOols();
            ash.needsFsRestart = true;
          } elseIf (act == "rm" && ept == "ool" && cmdl.length > 5) {
            List nxools = List.new();
            for (Mmep mmep in ools) {
              unless (mmep.ondid == cmdl[4] && mmep.ipos == cmdl[5]) {
                nxools += mmep;
              }
            }
            ools = nxools;
            saveOols();
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

  saveOols() {
    if (ools.isEmpty) {
      "empty ools".print();
      config.put(ooli, "");
    } else {
      String oolc = String.new();
      for (Mmep mmep in ools) {
        if (TS.notEmpty(oolc)) {
          oolc += ".";
        }
        oolc += mmep.ondid += "," += mmep.ipos += "," += mmep.spass;
      }
      ("conf putting oolc " + oolc).print();
      config.put(ooli, oolc);
    }
  }

  loadOols() {
    String oolcs = config.get(ooli);
    if (TS.notEmpty(oolcs)) {
      var oolce = oolcs.split(".");
      for (String oolc in oolce) {
        var oolcl = oolc.split(",");
        ools += Mmep.new(oolcl[0], oolcl[1], oolcl[2]);
        ("added ool " + oolc).print();
      }
    }
  }

  //String cmds = "dostate spass " + ipos + " setsw " + state + " e";
  //also need kdname/ondid
  //so, need this:
  //matrtype,ondid,spass,ipos
  //also, is it add, remove, or clear

  clearMmeps() {
    config.put(ooli, "");
  }

  start() {
    ooli = config.getPos("matr.ool");
    loadOols();
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

    Int oolslen = ools.length;
    emit(cc) {
      """
      int ol = beq->bevl_oolslen->bevi_int;

      std::shared_ptr<MatterOnOffLight> bevi_mool;

      if (ol > 0) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo0);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 1) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo1);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 2) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo2);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 3) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo3);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 4) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo4);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 5) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo5);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 6) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo6);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 7) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo7);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 8) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo8);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 9) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo9);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 10) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo10);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 11) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo11);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 12) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo12);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 13) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo13);
      bevi_mools.push_back(bevi_mool);
      }
      if (ol > 14) {
      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo14);
      bevi_mools.push_back(bevi_mool);
      }
      Matter.begin();
      """
    }
  }

  checkDoOol() {
    Int idx;
    Int st;
    emit(cc) {
      """
      if (oolChIdx >= 0 && oolChSt >= 0) {
        beq->bevl_idx = new BEC_2_4_3_MathInt(oolChIdx);
        beq->bevl_st = new BEC_2_4_3_MathInt(oolChSt);
        oolChIdx = -1;
        oolChSt = -1;
      }
      """
    }
    if (def(idx) && def(st)) {
      ("idx " + idx + " st " + st).print();
      Mmep mmep = ools.get(idx);
      if (st == 1) {
        String sts = "on";
      } else {
        sts = "off";
      }
      if (def(mmep)) {
         String mcmdres;
         String kdn = "CasNic" + mmep.ondid;
         String scmds = "dostate " + mmep.spass + " " + mmep.ipos + " setsw " + sts + " e";
         ("checkDoOol kdn scmds |" + kdn + "| |" + scmds + "|").print();
         ifNotEmit(noTds) {
          Embedded:Tds tdserver = ash.tdserver;
          if (def(tdserver)) {
            if (kdn == tdserver.myName) {
              //"call is coming from inside house".print();
              "selfgate".print();
              //mcmdres = doCmd("matr", scmds);
            } else {
              String rip = tdserver.getAddr(kdn);
              if (rip == CNS.undefined) {
                for (Int i = 0;i < 5;i++) {
                  ("no rip " + i).print();
                  tdserver.update();
                  ash.app.delay(25);
                  tdserver.update();
                  rip = tdserver.getAddr(kdn);
                  if (rip != CNS.undefined) {
                    break;
                  }
                }
              }
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
      }
    }
  }

  handleLoop() {
   checkDoOol();
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
