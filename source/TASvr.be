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
      String htp = "http://"
      Bool shouldSave = false;
      String swt = "sw";
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
        } else {
          "bad ehdm cmd".print();
          return("ehdmbadcmd");
        }
        return("ehdmok");
  }

  saveTads() {
    if (tads.isEmpty || true) {
      "empty tads".print();
      config.put(tadi, "");
    } else {
      String mc = String.new();
      for (Tad tad in tads) {
        if (TS.notEmpty(mc)) {
          mc += ".";
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
      var mce = mcs.split(".");
      for (String mc in mce) {
        var mcl = mc.split(",");
        tads += Tad.new(mcl[0], mcl[1], mcl[2]);
        ("added Tad " + mc).print();
      }
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
    //tadi = config.getPos("eh.tads");
    //"loading tads".print();
    //loadTads();

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
        if (nextSwCheckIdx >= tads.length) {
          nextSwCheckIdx = 0;
        }
      } elseIf (nowup > nextDisCheck) {
        nextDisCheck = nowup + disCheckIv;
        //"disCheck".print();
        String ina;
        String hna;
        String ada;
        emit(cc) {
          """
      #ifdef BEAR_ESP32
      int n = MDNS.queryService("esphomelib", "tcp");
      if (n == 0) {
        //Serial.println("no services found");
      } else {
        //Serial.print(n);
        //Serial.println(" service(s) found");
        for (int i = 0; i < n; ++i) {
          // Print details for each service found
          /*Serial.print("  ");
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.print(MDNS.instanceName(i));
          Serial.print(" - ");
          Serial.print(MDNS.hostname(i));
          Serial.print(" (");
          Serial.print(MDNS.address(i));
          Serial.print(":");
          Serial.print(MDNS.port(i));
          Serial.println(")");*/
          try {
            //String lip = WiFi.softAPIP().toString();
            String inaas = MDNS.instanceName(i);
            std::string inaa = std::string(inaas.c_str());
            beq->bevl_ina = new BEC_2_4_6_TextString(inaa);

            String hnaas = MDNS.hostname(i);
            std::string hnaa = std::string(hnaas.c_str());
            beq->bevl_hna = new BEC_2_4_6_TextString(hnaa);

            String adaas = MDNS.address(i).toString();
            std::string adaa = std::string(adaas.c_str());
            beq->bevl_ada = new BEC_2_4_6_TextString(adaa);
          } catch (...) {
            Serial.println("got exception doing queryservice");
          }
        }
      }
      //Serial.println();
      #endif
          """
        }
        upsertTad(ina, hna, ada);
      }
    }
  }

  upsertTad(String ina, String hna, String ada) {
    //("in upsertTad " + ina + " " + hna + " " + ada).print();
    if (TS.notEmpty(ina) && TS.notEmpty(hna) && TS.notEmpty(ada) && ina.has("plug")) {
      if (ina != hna) {
        ina += ":" += hna;
      }
      String wada = htp + ada;
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
        tad = Tad.new(swt, ina, wada); //will have to check for types later, maybe unknown is a type then check
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
    for (Tad ehd in tads) {
      var ehsc = Embedded:EhSc.new(ash, conPos, "sw", "", ehd);
      ehsc.initControl();
      ash.controls[conPos] = ehsc;
      conPos = conPos + 1;
    }
    ash.genControlDef();
  }

}

class Embedded:EhSc {

   new(_ash, Int _conPos, String _conName, String _conArgs, Tad _ehd) {
     slots {
       Embedded:AppShell ash = _ash;
       Config config = ash.config;
       Embedded:App app = ash.app;
       Int conPos = _conPos;
       String conType = _conName;
       Tad ehd = _ehd;
       String ok = CNS.ok;
       String ud = CNS.undefined;
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
       String getsw = "getsw";
       String on = CNS.on;
       String off = CNS.off;
       String setsw = "setsw";
     }
     fields {
       String sw;
     }
   }

   doState(List cmdl) String {
     "in dostate".print();
     String scm = cmdl[3];
     if (scm == getsw) {
      if (TS.notEmpty(sw)) {
        return(sw);
        } else {
        return(ud);
        }
     } elseIf (scm == setsw) {
        String insw = cmdl[4];
        if (insw == on) {
          sw = insw;
          "on".print();
        } elseIf (insw == off) {
          sw = insw;
          "off".print();
        }
        lastEvent.setValue(ash.nowup);
        ash.lastEventsRes = null;
     }
     return(ok);
   }

   clearStates() {
   }

}
