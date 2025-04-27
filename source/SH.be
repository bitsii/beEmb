/*
 * Copyright (c) 2021-2023, the Beysant Embedded Authors.
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
use Embedded:Config;

use Embedded:CommonNames as CNS;

class CNS {
   default() {
     fields {
       String on = "on";
       String off = "off"
       String ok = "ok";
       String undefined = "undefined";
     }
   }
}

class Embedded:AppShell {
   
   main() {
     fields {
       var app = Embedded:App.new();
       Config config = Config.new();
       Int nowup = Int.new();
       String lastEventsRes;
       List controls = List.new();
       List loopers = List.new();
       List sxd = List.new();
       List sxdi = List.new();
       Embedded:TCPClient concon;
       Bool needsFsRestart = false;
     }
     slots {
       Int shpassi;
       Int shspassi;
       Int shssidi;
       Int shseci;
       Int shdidi;
       Int shpowi;
       ifNotEmit(noSmc) {
         Int smcconi;
         Int smcui;
         Int smcpi;
       }

       Int zero = 0;
       Int nextUpdateCheck = 0;
       Int nextSwSpec = 0;
       Int nextRestart = 0;
       Int nextMaybeSave = 0;
       Int nextPow = 0;
       Int endResetByPow = 0;
       Int nextWifiCheck = 0;
       String slashn = "\n";
       String slashr = "\r";
       Bool needsRestart = false;
       Bool justSetWifi = false;
       Bool pastSetupTime = false;
       String did;
       String swSpec;
       String devCode;
       Bool resetByPow; //4 times 20 secs
       Bool inResetByPow = false;
       String readBuf = String.new();
       String supurl;
       String controlSpec;
       String controlDef;
       Bool needsNetworkInit = true;
       Bool needsBuildControls = true;
       Bool needsInitControls = true;
       Bool needsGc = false;
       Int looperI = Int.new();
       Int drift = 20;
     }
     ifNotEmit(noWeb) {
      slots {
        String htmlHead;
      }
     }
     app.plugin = self;

     "loading config".print();
     config.load();

     shpassi = config.getPos("sh.pass");
     shspassi = config.getPos("sh.spass");
     shssidi = config.getPos("sh.ssid");
     shseci = config.getPos("sh.sec");
     shdidi = config.getPos("sh.did");
     shpowi = config.getPos("sh.pow");
     ifNotEmit(noSmc) {
       smcconi = config.getPos("smc.con");
       smcui = config.getPos("smc.u");
       smcpi = config.getPos("smc.p");
     }

     ifEmit(dynConf) {
       slots {
         Bool lockConf;
       }
       String lockup = config.get(config.getPos("fc.lockConf"));
       if (TS.notEmpty(lockup) && lockup == CNS.on) {
         lockConf = true;
       } else {
         lockConf = false;
       }
     }

     app.uptime(nowup);
     nextUpdateCheck = nowup + 60000;
     nextSwSpec = nowup + 540000;
     nextMaybeSave = nowup + 15000;//15 secs
     nextPow = nowup + 45000;//45 secs
     endResetByPow = nowup + 1800000; //30 mins
     //nextWifiCheck = nowup + 180000;//3 mins
     nextWifiCheck = nowup + 45000;//45 secs
     
     //"making webPage".print();
     ifNotEmit(noWeb) {
     htmlHead = String.new();
     htmlHead += "HTTP/1.1 200 OK\r\n";
     htmlHead += "Content-type:text/html\r\n";
     htmlHead += "Connection: close\r\n";
     htmlHead += "\r\n";
     }
     
   }

   sendWebPage(treq) {
    ifNotEmit(noWeb) {
     treq.client.write(htmlHead);

     /*String htmlStart = "<html><head></head><body>";

     treq.client.write(htmlStart);

     String cmdForm = '''
     <form action="/" method="get">
     <input type="hidden" name="cmdform" value="cmdform"/>
     <br><label for="cmd">Your Command:</label><input type="text" name="cmd" size="64" maxLength="128"><br>
     <br><input type="submit" value="Send Command"></form>
     </form>
     ''';

     treq.client.write(cmdForm);

     String hexForm = '''
     <form action="/" method="get">
     <input type="hidden" name="hexform" value="hexform"/>
     <br><label for="hexit">What to Hex Encode:</label><input type="text" name="hexit" size="64" maxLength="128"><br>
     <br><input type="submit" value="Get Hex Encoded Value"></form>
     </form>
     ''';

     treq.client.write(hexForm);

     String htmlEnd = "</body></html>";

     treq.client.write(htmlEnd);*/

   }
   }

   initControls() {
     for (any control in controls) {
       control.initControl();
     }
   }

   doState(Int ctlPos, List cmdl) String {
     return(controls[ctlPos].doState(cmdl));
   }

   getLastEvents(List cmdl) String {
     if (undef(lastEventsRes)) {
      String les = String.new();
      if (TS.notEmpty(did)) {
        String d = ",";
        String cd = ";";
        Int conPos = 0;
        for (any control in controls) {
          String conType = control.conType;
          Int le = control.lastEvent;
          if (def(le)) {
            les += conType += d += conPos += d += le += cd;
          }
          conPos++;
        }
      }
      if (TS.isEmpty(les)) { les = CNS.undefined; }
      //("gle cmdl len " + cmdl.length).print();
      lastEventsRes = les;
     } else {
      les = lastEventsRes;
     }
     if (cmdl.length > 3) {
       les = cmdl[2] + " " + les;
     }
     return(les);
   }
   
   clearStates() {
     for (any control in controls) {
       control.clearStates();
     }
   }

   checkMakeIds() {
      slots {
        String pin;
      }
      fields {
        String myName;
      }
      ifEmit(dynConf) {
        pinpart = config.get(config.getPos("fc.scode"));
      }
      ifNotEmit(dynConf) {
        emit(cc) {
          """
          std::string pp = BE_SCODE;
          beq->bevl_pinpart = new BEC_2_4_6_TextString(pp);
          """
        }
      }
      if (TS.isEmpty(pinpart) || pinpart.length != 8) {
        Int shppi = config.getPos("sh.pinpart");
        String pinpart = config.get(shppi);
        if (TS.isEmpty(pinpart)) {
          pinpart = System:Random.getString(8).lowerValue();
          config.put(shppi, pinpart);
        }
      }
      pin = pinpart + pinpart;

      did = config.get(shdidi);
      if (TS.isEmpty(did)) {
        did = System:Random.getString(16).lowerValue();
        config.put(shdidi, did);
      }
      myName = "CasNic" + did;
   }

   loadPasses() {
      slots {
        String pass;
        String spass;
      }

      pass = config.get(shpassi);
      spass = config.get(shspassi);

   }

   makeSecQ() {
     slots {
       String secQ;
     }
     if (TS.notEmpty(did) && TS.notEmpty(spass)) {
       String tohash = spass.substring(0, 8) + did;
       String hdone;
       //return(prot.sha1hex(tosec).substring(0, 12));
       emit(cc) {
         """
#ifdef BEAR_ESP8266
      String lip = sha1(beq->bevl_tohash->bems_toCcString().c_str());
      std::string lips = std::string(lip.c_str());
      beq->bevl_hdone = new BEC_2_4_6_TextString(lips);
#endif
#ifdef BEAR_ESP32
  String msg = beq->bevl_tohash->bems_toCcString().c_str();
  // convert to char Array
  int ml = msg.length(); // number of BYTES of the message
  // +1, because of the 0-Terminator of Strings
  char msgArray[ml+1];
  msg.toCharArray(msgArray, ml+1);
  // Multiply the number of BYTES of the message by 8,
  // so we get the number of BITS of the message
  ml *= 8;
  uint32_t hash[5] = {}; // This will contain the 160-bit Hash
  SimpleSHA1::generateSHA((unsigned char*) msgArray, ml, hash);
  // output every element of the hash as the hexadecimal
  /*for (int i = 0; i < 5; i++) {
    Serial.print(hash[i], HEX);
  }*/
  char hexString[5 * 8 + 1]; // 5 hashes, each 8 hex digits, plus null terminator
  // Convert each uint32_t to hex
  for (size_t i = 0; i < 5; ++i) {
      for (int j = 7; j >= 0; --j) {
          hexString[i * 8 + j] = "0123456789abcdef"[hash[i] & 0xF];
          hash[i] >>= 4;
      }
  }
  hexString[40] = '\0'; // Null-terminate the string
  //Serial.println("hex string");
  //Serial.println(hexString);
  std::string lips = std::string(hexString);
  beq->bevl_hdone = new BEC_2_4_6_TextString(lips);
#endif
         """
       }
       secQ = hdone.substring(0, 12);
     } else {
       secQ = "Q";
     }
     //"secQ".print();
     //secQ.print();
   }

   buildSwInfoIn() {
     if (TS.isEmpty(swSpec)) {
       swSpec = "1,q,p4,p2.Unspeced.71";
     }
     var swl = swSpec.split(".");
     devCode = swl[1];
   }

   buildSwInfo() {
     if (TS.isEmpty(swSpec)) {
      ifEmit(dynConf) {
        swSpec = config.get(config.getPos("fc.swspec"));
      }
      ifNotEmit(dynConf) {
        emit(cc) {
          """
          std::string swspec = BESPEC_SW;
          bevp_swSpec = new BEC_2_4_6_TextString(swspec);
          """
        }
      }
     }
     buildSwInfoIn();
   }


   buildControl(Int conPos, String conName, String conArgs) {
     //sh no impl
     "buildControl called in SH".print();
     return(null);
   }

   buildControlsIn() {
     //config ctlconfver.control.ctlconf,args.control.ctlconf,args
     if (TS.isEmpty(controlSpec)) {
       controlSpec = "";
     }
     controlDef = "controldef,"
     var conl = controlSpec.split(".");
     Int i = 1;
     Int conPos = 0;
     while (i < conl.length) {
       if (conPos > 0) {
         controlDef += ",";
       }
       String conName = conl[i];
       i++;
       String conArgs = conl[i];
       controls.put(conPos, buildControl(conPos, conName, conArgs));
       controlDef += controls.get(conPos).conType;
       conPos = conPos + 1;
       i++;
     }
     ("controlDef " + controlDef).print();
   }

   buildControls() {
     if (TS.isEmpty(controlSpec)) {
       ifEmit(dynConf) {
         controlSpec = config.get(config.getPos("fc.conspec"));
       }
       ifNotEmit(dynConf) {
        emit(cc) {
          """
          std::string conspec = BESPEC_CON;
          bevp_controlSpec = new BEC_2_4_6_TextString(conspec);
          """
        }
       }
     }
     buildControlsIn();
   }

   initRandom() {
     var wifi = Embedded:Wifi.new();
     var rhash = wifi.macAddress;

     Int i = 0;
     for (String net in wifi.scanNetworks()) {
       rhash += net;
       i++;
       if (i > 7) { break; }
     }

     System:Random.seed(rhash.hash);

   }
   
   startLoop() {

     ifNotEmit(noWeb) {
       slots {
         Embedded:TinyWeb tweb;
       }
     }
     ifNotEmit(noSer) {
       slots {
        Embedded:SerServer serserver;
       }
     }
     ifNotEmit(noMdns) {
       slots {
        Embedded:Mdns mdserver;
       }
     }
     ifNotEmit(noTds) {
       fields {
        Embedded:Tds tdserver;
       }
     }
     ifNotEmit(noSmc) {
       slots {
        Embedded:Smc smcserver;
       }
     }
     ifNotEmit(noMatr) {
       slots {
        Embedded:MatrServer matrserver;
       }
     }
     slots {
       Embedded:TCPServer tcpserver;
       Embedded:TCPServer conserver;
     }

     app.wdtFeed();
     app.yield();
     //app.wdtDisable();
     app.wdtEnable(0);
     buildSwInfo();
     initRandom();
     checkMakeIds();
     loadPasses();
     makeSecQ();

     swSpec.print();
     "Device Id".print();
     did.print();
     "Pin".print();
     pin.print();
     swSpec.print();

     //Config c2 = Config.new();
     //c2.load();

     ifNotEmit(noSer) {
      serserver = Embedded:SerServer.new();
      serserver.start();
      serserver.enableDebug();
     }

   }

   networkInit() {
    checkWifiAp();
    if (def(Wifi.localIP)) {
      ("Local ip " + Wifi.localIP).print();
      if (Wifi.up) {

        tcpserver = Embedded:TCPServer.new(6420);
        tcpserver.start();

        String tccon;
        ifEmit(dynConf) {
          tccon = config.get(config.getPos("fc.tccon"));
          if (TS.isEmpty(tccon)) { tccon = CNS.off; }
        }
        ifNotEmit(dynConf) {
          emit(cc) {
            """
            std::string tccon = BE_TCPCONSOLE;
            beq->bevl_tccon = new BEC_2_4_6_TextString(tccon);
            """
          }
        }

        if (tccon == CNS.on) {
          conserver = Embedded:TCPServer.new(32259);
          conserver.start();
        }
        ("tcpconsole " + tccon).print();

        ifNotEmit(noWeb) {
         tweb = Embedded:TinyWeb.new();
         tweb.start();
        }

        //if (Wifi.isConnected) {
          ifNotEmit(noMdns) {
            mdserver = Embedded:Mdns.new(myName, "casnic", 6420, "tcp");
            mdserver.start();
          }
          ifNotEmit(noTds) {
            tdserver = Embedded:Tds.new(myName, self);
            tdserver.start();
          }
        //}

        ifEmit(smcGm) {
          //increase tdserver so I have addrs when I need them, I need moar than the uge
          tdserver.mW = 9;
          tdserver.mH = 6;
        }

        ifNotEmit(noSmc) {
          slots {
            String smccon;
            String smcu;
            String smcp;
          }
          smccon = config.get(smcconi);
          smcu = config.get(smcui);
          smcp = config.get(smcpi);
        }
        checkStartSmcServer();

        ifNotEmit(noMatr) {
          if (Wifi.isConnected) {
            matrserver = Embedded:MatrServer.new(self);
            matrserver.start();
          }
        }

       }
      }
   }

   checkStartSmcServer() {
      ifNotEmit(noSmc) {
        if (Wifi.isConnected) {
          if (undef(smcserver)) {
            if (TS.notEmpty(smccon) && TS.notEmpty(smcu) && TS.notEmpty(smcp)) {
              try {
                ("smccon " + smccon + " smcu " + smcu + " smcp " + smcp).print();
                var smccl = smccon.split(":");
                if (smccl[0] == "ssl") {
                  Bool qssl = true;
                } else {
                  qssl = false;
                }
                Int qpt = Int.new(smccl[2]);
                smcserver = Embedded:Smc.new(smccl[1], qpt, qssl, smcu, smcp);
              } catch (any smerr) {
                "got smerr".print();
                if (def(smerr)) {
                  smerr.print();
                }
              }
            } else {
              "smc not configed".print();
            }
          }
          if (def(smcserver)) {
            if (smcserver.connected == 1) {
              //"smcserver connected already".print();
            } else {
              if (smcserver.connect() == 0) {
                ifEmit(smcDm) {
                  smcserver.subscribe("casnic/cmd/" + did);
                }
                ifEmit(smcGm) {
                  smcserver.subscribe("casnic/cmds");
                }
              }
            }
          }
        }
      }
   }
   
  checkWifiAp() {
     //"in checkWifiAp".print();
     unless (Wifi.up && Wifi.mode == "station") {
       if (inResetByPow) {
         "in resetByPow, going to AP".print();
       } else {
        startWifi();
       }
      unless (Wifi.up) {
        initAp();
      }
     }
   }

   initAp() {
      slots {
        String apSsid;
        String apType; //O open, S secure, for wifi sec
        String hiddenCode; //include the pin part in the ssid or hide it, on is hide it
      }
      if (TS.isEmpty(apType)) {
        ifEmit(dynConf) {
          apType = config.get(config.getPos("fc.apType"));
          if (TS.isEmpty(apType)) { apType = "O"; }
        }
        ifNotEmit(dynConf) {
          emit(cc) {
            """
            std::string aptype = BE_APTYPE;
            bevp_apType = new BEC_2_4_6_TextString(aptype);
            """
          }
        }
      }
      if (TS.isEmpty(hiddenCode)) {
        ifEmit(dynConf) {
          hiddenCode = config.get(config.getPos("fc.hideCode"));
          if (TS.isEmpty(hiddenCode)) { hiddenCode = CNS.off; }
        }
        ifNotEmit(dynConf) {
          emit(cc) {
            """
            std::string hiddenCode = BE_HIDECODE;
            bevp_hiddenCode = new BEC_2_4_6_TextString(hiddenCode);
            """
          }
        }
      }
      if (TS.notEmpty(pin) && pin.length == 16) {
        String pinpt = pin.substring(0, 8);
        String sec = pin.substring(8, 16);
        String ssid = "Casnic" + apType + "-";
        var wifi = Embedded:Wifi.new();
        var nets = wifi.scanNetworks();
        var rand = System:Random.new();
        if (hiddenCode == CNS.on) {
          pinpt = "U";
        }
        String finssidp = ssid + pinpt + "-" + devCode + "-" + 6;
        while (nets.has(finssidp)) {
          finssidp = ssid + pinpt + "-" + devCode + "-" + rand.getIntMax(999);
        }
        apSsid = ssid + pinpt + "-" + devCode + "-42";
        ("Device setup code " + sec).print();
        if (apType == "O") {
          Wifi.new(finssidp, null).startAp();
        } else {
          Wifi.new(finssidp, sec).startAp();
        }
      }
   }
   
   startWifi() {
     //"in startWifi".print();
     slots {
       String ssid;
       String sec;
     }
     ssid = config.get(shssidi);
     sec = config.get(shseci);
     //("shssidi " + shssidi).print();
     //("shseci " + shseci).print();

     if (TS.notEmpty(ssid) && TS.notEmpty(sec)) {
       //("ssid " + ssid + " sec " + sec).print();
       ("ssid " + ssid).print();
       app.wdtFeed();
       app.yield();
       //app.wdtDisable();
       Wifi.new(ssid, sec).start();
     }
   }
   
   checkWifiUp() {
    //"checking if wifi up".print();
    unless (Wifi.isConnected || TS.isEmpty(ssid) || justSetWifi) {
       "wifi configured but not up".print();
       var wifi = Embedded:Wifi.new();
       var nets = wifi.scanNetworks();
       if (nets.has(ssid)) {
         "my ssid present".print();
         Wifi.new(ssid, sec).start();
       }
     }
     unless(needsFsRestart || needsRestart || justSetWifi) {
       if (Wifi.up && undef(tcpserver)) {
         needsNetworkInit = true;
       }
       checkStartSmcServer();
     }
   }

   sysupdate(String upurl) {
     ifNotEmit(noUpd) {
      "in update".print();
      "upurl".print();
      upurl.print();
      var eupd = Embedded:Update.new();
      eupd.updateFromUrl(upurl);
      "update done".print();
     }
   }

   initPow() {
     "init pow".print();
     String pow = config.get(shpowi);
     if (TS.notEmpty(pow)) {
       Int powi = Int.new(pow);
       powi++;
       if (powi > 4) {
         powi = 4;
       }
       if (powi == 4 && resetByPow) {
         inResetByPow = true;
         "now inResetByPow".print();
       }
     } else {
       powi = 1;
     }
     ("powi " + powi).print();
     config.put(shpowi, powi.toString());
   }

   clearPow() {
     if (TS.notEmpty(config.get(shpowi))) {
      "clearing powi".print();
      config.put(shpowi, "");
     }
   }

   handleLoop() {
     app.wdtFeed();
     app.yield();
     //app.wdtDisable();
     app.uptime(nowup);
     if (needsGc) {
       needsGc = false;
       app.maybeGc();
       return(self);
     }
     if (undef(resetByPow)) {
       String rbps;
       ifEmit(dynConf) {
         rbps = config.get(config.getPos("fc.rbps"));
         if (TS.isEmpty(rbps)) { rbps = CNS.on; }
       }
       ifNotEmit(dynConf) {
        emit(cc) {
            """
            std::string rbps = BE_RESETBYPOW;
            beq->bevl_rbps = new BEC_2_4_6_TextString(rbps);
            """
          }
        }
        if (rbps == CNS.off) {
          resetByPow = false;
        } else {
          resetByPow = true;
        }
        ("resetByPow set " + resetByPow).print();
        initPow();
        needsGc = true;
        return(self);
     }
     if (needsBuildControls) {
       needsBuildControls = false;
       buildControls();
       needsGc = true;
       return(self);
     }
     if (needsInitControls) {
       needsInitControls = false;
       initControls();
       needsGc = true;
       return(self);
     }
     if (needsNetworkInit) {
       needsNetworkInit = false;
       networkInit();
       needsGc = true;
       return(self);
     }
     if (nowup > nextMaybeSave) {
      nextMaybeSave = nowup + 15000;//15 secs
      if (config.changed) {
        "maybeSave config".print();
        config.maybeSave();
      }
      needsGc = true;
      return(self);
     }
     if (nowup > nextPow) {
      nextPow = nowup + 45000;//45 secs
      clearPow();
      return(self);
     }
     if (nowup > endResetByPow) {
       endResetByPow = nowup + 900000; //15 mins
       pastSetupTime = true;
       if (inResetByPow) {
        inResetByPow = false;
        needsFsRestart = true;
        "endResetByPow".print();
       }
       return(self);
     }
     if (nowup > nextWifiCheck) {
      //nextWifiCheck = nowup + 180000;//3 mins
      nextWifiCheck = nowup + 45000;//45 secs
      unless (inResetByPow) {
        checkWifiUp();
        needsGc = true;
        return(self);
      }
     }
     if (nowup > nextSwSpec) {
      nextSwSpec = nowup + 540000;
      swSpec.print();
      nowup.print();
      return(self);
     }
     if (nextRestart > zero && nowup > nextRestart) {
      "restarting from nextRestart".print();
      Wifi.stop();
      Wifi.clearAll();
      app.restart();
      return(self);
     }
     if (nowup > nextUpdateCheck) {
      nextUpdateCheck = nowup + 60000;
      if (def(supurl) && TS.notEmpty(supurl)) {
        String upurl = supurl;
        supurl = null;
        sysupdate(upurl);
      }
      return(self);
     }
     ifNotEmit(noSer) {
      if (def(serserver) && serserver.available) {
        "got serpay".print();
        String serpay = serserver.checkGetPayload(readBuf, slashn);
      }
      if (TS.notEmpty(serpay)) {
        try {
            //"doing serpay".print();
            String scmdres = doCmd("serial", serpay);
            if (TS.isEmpty(scmdres)) {
              "scmdres empty".print();
            } else {
              ("scmdres " + scmdres).print();
            }
          } catch (any sdce) {
            "error handling command".print();
            sdce.print();
          }
          "serpay returning now".print();
          //app.yield();
          //"now".print();
          return(self);
      }
     }
     ifNotEmit(noSmc) {
      if (def(smcserver)) {
        String smcpay = smcserver.checkGetPayload(readBuf);
      }
      if (TS.notEmpty(smcpay)) {
        try {
            "doing smcpay".print();
            String mcmdres;
            ifEmit(smcGm) {
              "in smcGm".print();
              smcpay.print();
              //rel1:CasNicQDHCWAEVPRRPYGTN;getlastevents c30e787d40fd RQKGXNKWTNCKICDK,GLXMUARONSPY e
              if (TS.notEmpty(smcpay) && smcpay.begins("rel1:")) {
                String kdn = smcpay.substring(smcpay.find(":") + 1, smcpay.find(";"));
                String scmds = smcpay.substring(smcpay.find(";") + 1, smcpay.length);
                ("smbGm kdn scmds |" + kdn + "| |" + scmds + "|").print();
                if (kdn == myName) {
                  //"call is coming from inside house".print();
                  "selfgate".print();
                  mcmdres = doCmd("mq", scmds);
                } else {
                  ifNotEmit(noTds) {
                    if (def(tdserver)) {
                        String rip = tdserver.reallyGetAddr(kdn);
                        if (rip == CNS.undefined) {
                          "no rip".print();
                        } else {
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
                        }
                    }
                  }
                }
              } else {
                "smcGm smcpay malformed".print();
              }
            }
            ifEmit(smcDm) {
              //smcpay.print();
              mcmdres = doCmd("mq", smcpay);
            }
            if (TS.isEmpty(mcmdres)) {
              "mcmdres empty".print();
            } else {
              ("mcmdres " + mcmdres).print();
              //send back res to mq here
              //iv,reid( )
              Int mfc = mcmdres.find(",");
              Int mfs = mcmdres.find(" ");
              if (def(mfc) && def(mfs)) {
                String reid = mcmdres.substring(mfc + 1, mfs);
                //("mq reid " + reid).print();
                smcserver.publish("casnic/res/" + reid, mcmdres);
              }
            }
          } catch (any mdce) {
            "error handling command".print();
            mdce.print();
          }
          return(self);
      }
     }
     ifNotEmit(noWeb) {
      if (def(tweb)) {
        var treq = tweb.checkGetRequest();
        if (def(treq)) {
          //"got treq".print();
          String qs = treq.checkGetQueryString(readBuf);
          if (TS.notEmpty(qs)) {
            "got qs, it follows".print();
            qs.print();
            if (qs == "/") {
              "base qs sending webpage".print();
              sendWebPage(treq);
              needsGc = true;
            } elseIf (qs.begins("/?")) {
              var qspso = qs.split("&");
              for (String qspsi in qspso) {
                if (TS.notEmpty(qspsi)) {
                  //("got qspsi " + qspsi).print();
                  var qsps = qspsi.split("=");
                  //gocha = cmd cannnnot be the first param, is it will have a /?
                  if (qsps.length > 1 && def(qsps[0]) && TS.notEmpty(qsps[1])) {
                    if (qsps[0] == "cmd") {
                      //("got cmd " + qsps[1]).print();
                      String cdec = Encode:Url.decode(qsps[1]);
                      //("cdec " + cdec).print();
                      try {
                          String wcmdres = doCmd("web", cdec);
                          treq.client.write(htmlHead); //ok headers
                          if (TS.isEmpty(wcmdres)) {
                            treq.client.write("wcmdres empty");
                          } else {
                            treq.client.write(wcmdres);
                          }
                        } catch (any wdce) {
                          "error handling command".print();
                          wdce.print();
                        }
                    } elseIf (qsps[0] == "hexit") {
                      String hi = Encode:Url.decode(qsps[1]);
                      hi = Encode:Hex.encode(hi);
                      treq.client.write(htmlHead); //ok headers
                      treq.client.write(hi);
                    }
                  }
                }
              }
            }
          }
          //treq.printHeaders();
          treq.close();
          return(self);
        }
      }
     }
     if (def(tcpserver)) {
      var preq = tcpserver.checkGetClient();
      if (def(preq)) {
        //"got preq".print();
        String ppay = preq.checkGetPayload(readBuf, slashn);
        if (TS.notEmpty(ppay)) {
            try {
                String pcmdres = doCmd("tcp", ppay);
                if (TS.isEmpty(pcmdres)) {
                  "pcmdres empty".print();
                } else {
                  ("pcmdres " + pcmdres).print();
                  preq.write(pcmdres);
                  preq.write(slashr);
                  preq.write(slashn);
                  "pcmdres send done".print();
                }
              } catch (any pdce) {
                "error handling command".print();
                pdce.print();
              }
          }
        preq.close();
        return(self);
      }
     }
     ifNotEmit(noMatr) {
       if (def(matrserver)) {
        matrserver.handleLoop();
       }
     }
     if (def(conserver)) {
       if (undef(concon)) {
        concon = conserver.checkGetClient();
       } else {
        unless (concon.connected) {
          concon = null;
        }
       }
     }
     looperI.setValue(zero);
     while (looperI < loopers.length) {
       loopers.get(looperI).handleLoop();
       looperI++;
     }
     ifNotEmit(noMdns) {
      if (def(mdserver)) {
        mdserver.update();
      }
     }
     ifNotEmit(noTds) {
      if (def(tdserver)) {
        tdserver.update();
      }
     }
     if (needsRestart) {
       needsRestart = false;
       "prep restart needsRestart".print();
        nextRestart = nowup + 2000;
     }
     if (needsFsRestart) {
       needsFsRestart = false;
       "maybeSave config".print();
       config.maybeSave();
       needsRestart = true;
     }
   }

   doCmd(String channel, String cmdline) String {
     app.wdtFeed();
     app.yield();
     if (TS.isEmpty(cmdline)) {
       return("cmdline empty");
     }
     if (TS.isEmpty(channel)) {
       return("channel empty");
     }
     //check max length and num of spaces
     ("cmd channel").print();
     channel.print();
     ("cmdline").print();
     cmdline.print();
     var cmdl = cmdline.split(" ");
     //get rid of trailing newline NOW WE DOWN'T, ADD SOMETHING ON THE BACK
     //if (channel == "serial" && cmdl.length > 0) {
     //  cmdl.put(cmdl.length - 1, cmdl.get(cmdl.length - 1).swap("\n", ""));
     //}
     //if (channel == "tcp" && cmdl.length > 0) {
     //  cmdl.put(cmdl.length - 1, cmdl.get(cmdl.length - 1).swap("\r\n", ""));
     //}
     if (cmdl.length > 0 && (cmdl[0].ends("p4") || cmdl[0].ends("p5") || cmdl[0].ends("p6"))) {
       return(doCmdlSec(channel, cmdl));
     }
     return(doCmdl(channel, cmdl));
   }

   doCmdlSec(String channel, List cmdl) String {
     if (cmdl.length > 4) {
       List cmdn = List.new();
       String hdone;
       //sporap1 iv
       "doing cmdlsec".print();
       String spw = "";
       if (cmdl[0].begins("sp")) {
         spw = spass;
       } elseIf (cmdl[0].begins("ap")) {
         spw = pass;
       } else {
         ("unknown secsceme " + cmdl[0]).print();
       }
       ifNotEmit(noAes) {
        if (cmdl[0].ends("p5")) {
          "decrypting".print();
          String dhex = Encode:Hex.decode(cmdl[4]);
          String dcryp = Embedded:Aes.decrypt(cmdl[1], spw, dhex);
          "dcryp".print();
          dcryp.print();
          var cadd = dcryp.split(" ");
          for (Int k = 0;k < cadd.length;k++) {
            cmdl[k + 4] = cadd[k];
          }
        }
       }
       Int abeg = 4;
       String tohash = cmdl[1] + "," + spw + "," + cmdl[3] + ",";
       if (cmdl[0].ends("p6")) {
         abeg = 5;
         tohash = tohash + cmdl[4] + ",";
       }
       Int toc = cmdl.length - 1;
        String sp = " ";
        for (Int j = abeg.copy();j < toc;j++) {
          tohash += cmdl[j] += sp;
        }
       //("tohash |" + tohash + "|").print();
       emit(cc) {
         """
#ifdef BEAR_ESP8266
      String lip = sha1(beq->bevl_tohash->bems_toCcString().c_str());
      std::string lips = std::string(lip.c_str());
      beq->bevl_hdone = new BEC_2_4_6_TextString(lips);
#endif
#ifdef BEAR_ESP32
  String msg = beq->bevl_tohash->bems_toCcString().c_str();
  // convert to char Array
  int ml = msg.length(); // number of BYTES of the message
  // +1, because of the 0-Terminator of Strings
  char msgArray[ml+1];
  msg.toCharArray(msgArray, ml+1);
  // Multiply the number of BYTES of the message by 8,
  // so we get the number of BITS of the message
  ml *= 8;
  uint32_t hash[5] = {}; // This will contain the 160-bit Hash
  SimpleSHA1::generateSHA((unsigned char*) msgArray, ml, hash);
  // output every element of the hash as the hexadecimal
  /*for (int i = 0; i < 5; i++) {
    Serial.print(hash[i], HEX);
  }*/
  char hexString[5 * 8 + 1]; // 5 hashes, each 8 hex digits, plus null terminator
  // Convert each uint32_t to hex
  for (size_t i = 0; i < 5; ++i) {
      for (int j = 7; j >= 0; --j) {
          hexString[i * 8 + j] = "0123456789abcdef"[hash[i] & 0xF];
          hash[i] >>= 4;
      }
  }
  hexString[40] = '\0'; // Null-terminate the string
  //Serial.println("hex string");
  //Serial.println(hexString);
  std::string lips = std::string(hexString);
  beq->bevl_hdone = new BEC_2_4_6_TextString(lips);
#endif
         """
       }
       if (TS.notEmpty(hdone)) {
         //("hdone " + hdone).print();
         hdone = secTime(cmdl[1], hdone, cmdl[3]);
         if (TS.notEmpty(cmdl[2]) && hdone == cmdl[2]) {
           ("hsec passed").print();
           cmdl.put(abeg + 1, spw);
           for (Int i = abeg.copy();i < cmdl.length;i++) {
             cmdn += cmdl[i];
           }
         } else {
           ("hsec failed").print();
         }
       }
       String cdres = doCmdl(channel, cmdn);
       ifNotEmit(noAes) {
        if (cmdl[0].ends("p5") && TS.notEmpty(cdres)) {
          "encrypting".print();
          String ecryp = Embedded:Aes.encrypt(cmdl[1], spw, cdres);
          cdres = Encode:Hex.encode(ecryp);
        }
       }
       if (cmdl[0].ends("p6") && TS.notEmpty(cdres)) {
        cdres = cmdl[1] + "," + cmdl[4] + " " + cdres;
       }
       return(cdres);
     }
     return("nodice");
   }

   secTime(String iv, String hdone, String tesh) String {
     slots {
       Int lsec; //lsec last sent seconds since epoch
       List ivs;
       Int ivpt;
     }
     if (undef(ivs)) { ivs = List.new(10); }
     for (var ti in ivs) {
       if (iv == ti) {
         return("f");
       }
     }
     if (undef(ivpt) || ivpt > 9) { ivpt = 0; }
     else { ivpt++; }
     //tesh seconds since epoch passed in
     //drift seconds back that's ok
     Int teshi = app.strToInt(tesh);
     //("techi is " + teshi).print();
     if (undef(lsec)) {
      //"undef lsec".print();
       teshi -= drift;
       lsec = teshi;
       ivs[ivpt] = iv;
       return(hdone);
     }
     //new sent value must be > (last sent value - Xtolerance) (5secs? 10?)
     //("lsec is " + lsec).print();
     if (teshi > lsec) {
       //"passed secTime gt".print();
       teshi -= drift;
       lsec = teshi;
       ivs[ivpt] = iv;
       return(hdone);
     } else {
       //"failed secTime lt".print();
     }
     return("f");
   }

   getvisnets(List cmdl) String {
     slots {
       List visnets;
     }
     if (undef(visnets)) {
       var wifi = Embedded:Wifi.new();
       visnets = wifi.scanNetworks();
     }
      if (cmdl.length > 1) {
        String st = cmdl[1];
        if (st.isInteger) {
          Int sti = Int.new(st);
        }
      }
      if (undef(sti)) {
        sti = 0;
      }
      //"sti".print();
      //sti.print();

      Int i = 0;
      Int j = 0;
      String res = "ssids";
      for (String net in visnets) {
        i++;
        if (i > sti) {
          j++;
          res += ":" += Encode:Hex.encode(net);
          if (j > 3) { break; }
        }
      }
      return(res);
   }
   
   doCmdl(String channel, List cmdl) String {
     app.maybeGc();
     app.wdtFeed();
     app.yield();
     needsGc = true;
     if (cmdl.length < 1) {
       return("no cmd specified");
     }
     String cmd = cmdl[0];
     //("cmd is " + cmd).print();
     if (cmd == "getapssid") {
       if (def(apSsid)) {
         return(apSsid);
       } else {
         return("");
       }
     } elseIf (cmd == "getlastevents" && cmdl[1] == secQ) {
       stateres = getLastEvents(cmdl);
       return(stateres);
     } elseIf (cmd == "previsnets") {
       if (def(apSsid)) {
         return(getvisnets(cmdl));
       } else {
         return("on network nope");
       }
     } elseIf (cmd == "dostate" && cmdl.length > 3 && cmdl[3].begins("get") && cmdl[1] == secQ) {
       Int ctlPos = app.strToInt(cmdl[2]);
       stateres = doState(ctlPos, cmdl);
       //("dosl cmdl len " + cmdl.length).print();
       if (cmdl.length > 5) {
         stateres = cmdl[4] + " " + stateres;
       }
       return(stateres);
     } elseIf (cmd == "getstatexd" && cmdl[1] == secQ) {
       ctlPos = app.strToInt(cmdl[2]);
       xd = sxd[ctlPos];
       if (TS.isEmpty(xd)) {
          xdi = sxdi[ctlPos];
          if (undef(xdi)) {
            xdi = config.getPos("xd." + ctlPos);
            sxdi[ctlPos] = xdi;
          }
          xd = config.get(xdi);
          if (TS.isEmpty(xd)) {
            xd = CNS.undefined;
          }
          sxd[ctlPos] = xd;
       }
       if (TS.notEmpty(xd) && cmdl.length > 4) {
          xd = cmdl[3] + " " + xd;
       }
       return(xd);
     }
     if (cmd.begins("do") || cmd == "getcontroldef" || cmd == "gettda") {
        //"got dostate".print();
        //state password check
        unless (channel == "serial") {
          if (TS.isEmpty(spass)) {
            return("State Password Must Be Set");
          }
          String inpass = cmdl[1];
          if (TS.isEmpty(inpass)) {
            return("State password must be provided");
          }
          if (inpass != spass) {
            return("State Password Incorrect");
          }
        }
        if (cmd == "dostate") {
          ctlPos = app.strToInt(cmdl[2]);
          String stateres = doState(ctlPos, cmdl);
          return(stateres);
        } elseIf (cmd == "dostatexd") {
          ctlPos = app.strToInt(cmdl[2]);
          String xd = cmdl[5];
          sxd[ctlPos] = xd;
          Int xdi = sxdi[ctlPos];
          if (undef(xdi)) {
            xdi = config.getPos("xd." + ctlPos);
            sxdi[ctlPos] = xdi;
          }
          config.put(xdi, xd);
          stateres = doState(ctlPos, cmdl);
          return(stateres);
        } elseIf (cmd == "doswspec") {
          return(swSpec);
        } elseIf (cmd == "gettda") {
          ifNotEmit(noTds) {
            if (def(tdserver)) {
              return(tdserver.getAddr(cmdl[2]));
            }
          }
          return(CNS.ok);
        } else {
          if (def(controlDef)) {
            return(controlDef);
          } else {
            return("controldef,");
          }
        }
     }

    if (cmd == "allset") {

      if (pastSetupTime) {
        return("Error, must setup w/in 15 mins of power on.");
      }

      String inpin = cmdl[1];
      if (TS.notEmpty(pin)) {
        if (TS.isEmpty(inpin)) {
          return("Error, pin was not sent");
        } elseIf (pin != inpin) {
          return("Error, pin is incorrect");
        }
      } else {
        return("Error, pin must be set");
      }

      String newpass = cmdl[2];
      if (inResetByPow) {
        "in resetByPow skip pass".print();
      } elseIf (TS.notEmpty(pass)) {
        if (TS.isEmpty(newpass)) {
          return("Error, pass was not sent");
        } elseIf (pass != newpass) {
          return("Error, pass is incorrect");
        }
      }

      if (TS.isEmpty(newpass)) {
        return("Error, new password is required");
      } else {
        config.put(shpassi, newpass);
        pass = newpass;
      }

      String newspass = cmdl[3];
      if (TS.isEmpty(newspass)) {
        return("Error, new spass is required");
      }
      spass = newspass;
      config.put(shspassi, spass);

      String newdid = cmdl[4];
      if (TS.notEmpty(did) && did.length == 16) {
        did = newdid;
        config.put(shdidi, did);
      } else {
        return("Error, newdid sized 16 required");
      }
      config.put(shpowi, "");
      return("allset done p4");
      //return("allset done");

      }

     //password check
     unless (channel == "serial") {
        if (TS.isEmpty(pass)) {
          return("Device Password Must Be Set");
        }
        inpass = cmdl[1];
        if (TS.isEmpty(inpass)) {
          return("Device password must be provided");
        }
        if (inpass != pass) {
          return("Device Password Incorrect");
        }
     }

     if (cmd == "setwifi") {
        if (cmdl[2] == "hex") {
          ssid = Encode:Hex.decode(cmdl[3]);
          sec = Encode:Hex.decode(cmdl[4]);
        } else {
          ssid = cmdl[3];
          sec = cmdl[4];
        }
        if (TS.notEmpty(ssid)) {
          //("got ssid " + ssid).print();
          config.put(shssidi, ssid);
          if (TS.notEmpty(sec)) {
            //("got sec " + sec).print();
            config.put(shseci, sec);
          } else {
            ("sec missing").print();
            config.put(shseci, "");
          }
          justSetWifi = true;
          return("Wifi Setup Written");
        } else {
          ("ssid missing").print();
          config.put(shssidi, "");
          config.put(shseci, "");
          justSetWifi = true;
          return("Wifi Setup cleared");
        }
     } elseIf (cmd == "setsmc") {
       ifNotEmit(noSmc) {
         //cmds = "setsmc " + devPass + " nohex " + smch + " " + bkrs[2] + " " + bkrs[0] + " " + mqr["mqttUser"] + " " + mqr["mqttPass"] + " e";
        if (cmdl.length > 5) {
        if (cmdl[2] == "hex") {
          smccon = Encode:Hex.decode(cmdl[3]);
          smcu = Encode:Hex.decode(cmdl[4]);
          smcp = Encode:Hex.decode(cmdl[5]);
        } else {
          smccon = cmdl[3];
          smcu = cmdl[4];
          smcp = cmdl[5];
        }
          "setting smc".print();
          config.put(smcconi, smccon);
          config.put(smcui, smcu);
          config.put(smcpi, smcp);
        } else {
          "clearing smc".print();
        }
        }
        return("smcok");
     } elseIf (cmd == "matrep") {
       ifNotEmit(noMatr) {
         if (def(matrserver)) {
           return(matrserver.handleCmdl(cmdl));
         }
        }
        return("unsupported");
     } elseIf (cmd == "reset") {
      reset();
      return("Device reset");//we look for this result, don't change
    } elseIf (cmd == "putconfigs") {
      ifEmit(dynConf) {
        if (lockConf) {
          return("lockConf on, no putconfig");
        }
        if (cmdl[2] == "vhex") {
          Bool deHex = true;
        } else {
          deHex = false;
        }
        Int cmdle = cmdl.length - 1;
        for (Int k = 3;k < cmdle;k++) {
          String key = cmdl[k];
          k++;
          if (k < cmdle) {
            String value = cmdl[k];
          } else {
            value = null;
          }
          if (TS.notEmpty(key)) {
            if (key.begins("fc.")) {
              Int keyi = config.getPos(key);
              if (TS.isEmpty(value)) {
                config.put(keyi, "");
              } else {
                if (deHex) {
                  value = Encode:Hex.decode(value);
                }
                config.put(keyi, value);
              }
            } else {
              return("configs failed bad key");
            }
          }
        }
        return("configs set");
        }
     } elseIf (cmd == "maybesave") {
        config.maybeSave();
        needsGc = true;
        return("maybe saved");
     } elseIf (cmd == "sysupdate") {
        supurl = cmdl[2];
        return("set supurl");
     } elseIf (cmd == "restart") {
       //"got restart".print();
       needsFsRestart = true;
       return("Will restart soonish");
     } else {
       return("unrecognized command");
     }
      return("Something's fishy");
   }

   reset() {
    config.put(shpassi, "");
    config.put(shssidi, "");
    config.put(shseci, "");
    config.put(shspassi, "");
    config.put(shdidi, "");
    clearStates();
    ifNotEmit(noMatr) {
      if (def(matrserver)) {
        matrserver.clearMeps();
        matrserver.decommission();
      }
    }
    ifNotEmit(noSmc) {
      config.put(smcconi, "");
      config.put(smcui, "");
      config.put(smcpi, "");
    }
    needsFsRestart = true;
   }
   
}
