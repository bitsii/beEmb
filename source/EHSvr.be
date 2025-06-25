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

use Embedded:CommonNames as CNS;
use Embedded:Ehd;

class Embedded:EHomeServer {

  new(_ash) self {
    slots {
      Embedded:AppShell ash = _ash;
      Config config = ash.config;
      Int ehdi;
      List ehds = List.new();
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
          clearEhds();
          //ash.needsFsRestart = true;
        } elseIf (cmdl.length > 3) {
          String act = cmdl[2];
          if (act == "add" && cmdl.length > 6) {
            if (ehds.length >= 15) {
              return("ehdmtoomany");
            }
            ehds += Ehd.new(cmdl[3], cmdl[4], cmdl[5], cmdl[6]);
            saveEhds();
            //ash.needsFsRestart = true;
          } elseIf (act == "rm" && cmdl.length > 5) {
            List nx = List.new();
            for (Ehd mmep in ehds) {
              unless (mmep.ondid == cmdl[4] && mmep.ipos == cmdl[5]) {
                nx += mmep;
              }
            }
            ehds = nx;
            saveEhds();
            //ash.needsFsRestart = true;
          } else {
            ("unknown ehdm act " + act).print();
            return("ehdmbadact");
          }
        } else {
          "bad ehdm cmd".print();
          return("ehdmbadcmd");
        }
        return("ehdmok");
  }

  saveEhds() {
    if (ehds.isEmpty) {
      "empty ehds".print();
      config.put(ehdi, "");
    } else {
      String mc = String.new();
      for (Ehd mmep in ehds) {
        if (TS.notEmpty(mc)) {
          mc += ".";
        }
        mc += mmep.met += "," += mmep.ondid += "," += mmep.ipos += "," += mmep.spass;
      }
      ("conf putting mc " + mc).print();
      config.put(ehdi, mc);
    }
  }

  loadEhds() {
    String mcs = config.get(ehdi);
    if (TS.notEmpty(mcs)) {
      var mce = mcs.split(".");
      for (String mc in mce) {
        var mcl = mc.split(",");
        ehds += Ehd.new(mcl[0], mcl[1], mcl[2], mcl[3]);
        ("added Ehd " + mc).print();
      }
    }
  }

  //String cmds = "dostate spass " + ipos + " setsw " + state + " e";
  //also need kdname/ondid
  //so, need this:
  //matrtype,ondid,spass,ipos
  //also, is it add, remove, or clear

  clearEhds() {
    config.put(ehdi, "");
  }

  start() {
    ehdi = config.getPos("eh.ehds");
    "loading ehds".print();
    loadEhds();

    Int ehdslen = ehds.length;

    for (Int i = 0;i < ehdslen;i++) {
      if (i >= 15) {
        break;
      }
      Ehd mmep = ehds[i];
      if (def(mmep)) {
        Int meti;
        if (mmep.met == "ool") {
          meti = 0;
        } elseIf (mmep.met == "dl") {
          meti = 1;
        }
      }
    }

    if (ehdslen <= 0) { Int ivdiv = 1; } else { ivdiv = ehdslen; }
    slots {
      Int swCheckIv = 36000 / ivdiv;//millis per each check on any given device
      Int nextSwCheck = ash.nowup + swCheckIv;
      Int nextSwCheckIdx = 0;
      Int disCheckIv = 20000;
      Int nextDisCheck = ash.nowup + 2000;
      //Int nextDisCheck = ash.nowup + disCheckIv;
    }

  }

  checkNDo() {
    Int didact;
    if (undef(didact)) {
      Int nowup = ash.nowup;
      if (nowup > nextSwCheck) {
        nextSwCheck = nowup + swCheckIv;
        if (nextSwCheckIdx >= ehds.length) {
          nextSwCheckIdx = 0;
        }
      } elseIf (nowup > nextDisCheck) {
        nextDisCheck = nowup + disCheckIv;
        "disCheck".print();
        Int qsr = Int.new();
        emit(cc) {
          """
      #ifdef BEAR_ESP32
      int c = MDNS.queryService("esphomelib", "tcp");
      beq->bevl_qsr->bevi_int = c;
      #endif
          """
        }
        ("qsr " + qsr).print();
      }
    }
  }

  handleLoop() {
   checkNDo();
  }

}
