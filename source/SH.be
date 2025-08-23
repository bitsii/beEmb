/*
 * Copyright (c) 2021-2023, the Brace Embedded Authors.
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
       String fail = "fail";
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
       Bool needsFsRestart = false;
       String swSpec;
     }
     slots {
       Int shpowi;

       Int zero = 0;
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
       String devCode;
       Bool resetByPow; //4 times 20 secs
       Bool inResetByPow = false;
       String readBuf = String.new();
       String controlSpec;
       String controlDef;
       Int controlHash;
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

     shpowi = config.getPos("sh.pow");

     app.uptime(nowup);
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
     //"in doState".print();
     any con = controls[ctlPos];
     if (def(con)) {
       //"calling con".print();
       return(con.doState(cmdl));
     }
     return(null);
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
        if (def(controlHash)) {
          les += "sccf" += d += conPos += d += controlHash += cd;
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
      emit(cc) {
        """
        std::string pp = BE_SCODE;
        beq->bevl_pinpart = new BEC_2_4_6_TextString(pp);
        """
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


      Int shdidi = config.getPos("sh.did");
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

      Int shpassi = config.getPos("sh.pass");
      pass = config.get(shpassi);
      Int shspassi = config.getPos("sh.spass");
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
      emit(cc) {
        """
        std::string swspec = BESPEC_SW;
        bevp_swSpec = new BEC_2_4_6_TextString(swspec);
        """
      }
     }
     buildSwInfoIn();
   }


   buildControl(Int conPos, String conName, String conArgs) {
     //sh no impl
     "buildControl called in SH".print();
     return(null);
   }

   genControlDef() {
     controlDef = "controldef,"
     Int conPos = 0;
     while (conPos < controls.length) {
       if (conPos > 0) {
         controlDef += ",";
       }
       controlDef += controls.get(conPos).conType;
       conPos = conPos + 1;
     }
     ("controlDef " + controlDef).print();
     if (TS.notEmpty(swSpec)) {
       String chs = swSpec + ".," + controlDef;
       controlHash = chs.hash.absValue();
     }
     lastEventsRes = null;
   }

   buildControlsIn() {
     //config ctlconfver.control.ctlconf,args.control.ctlconf,args
     if (TS.isEmpty(controlSpec)) {
       controlSpec = "";
     }
     var conl = controlSpec.split(".");
     Int i = 1;
     Int conPos = 0;
     while (i < conl.length) {
       String conName = conl[i];
       i++;
       String conArgs = conl[i];
       controls.put(conPos, buildControl(conPos, conName, conArgs));
       conPos = conPos + 1;
       i++;
     }
     genControlDef();
   }

   buildControls() {
     if (TS.isEmpty(controlSpec)) {
      emit(cc) {
        """
        std::string conspec = BESPEC_CON;
        bevp_controlSpec = new BEC_2_4_6_TextString(conspec);
        """
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
       fields {
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
     ifEmit(ehSvr) {
       slots {
        Embedded:EHomeServer ehserver;
       }
     }
     ifEmit(taSvr) {
       slots {
        Embedded:TAServer taserver;
       }
     }
     slots {
       Embedded:TCPServer tcpserver;
     }

     ifEmit (tcCon) {
       slots {
        Embedded:TCPServer conserver;
      }
      fields {
        Embedded:TCPClient concon;
      }
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

        ifEmit (tcCon) {
        String tccon;
        emit(cc) {
          """
          std::string tccon = BE_TCPCONSOLE;
          beq->bevl_tccon = new BEC_2_4_6_TextString(tccon);
          """
        }

        if (tccon == CNS.on) {
          conserver = Embedded:TCPServer.new(32259);
          conserver.start();
        }
        ("tcpconsole " + tccon).print();
        }

        ifNotEmit(noWeb) {
         tweb = Embedded:TinyWeb.new();
         tweb.start();
        }

        ifNotEmit(noMdns) {
          mdserver = Embedded:Mdns.new(myName, "casnic", 6420, "tcp");
          mdserver.start();
        }
        checkStartUpServer();
        checkStartTdServer();

        ifNotEmit(noSmc) {
          slots {
            String smccon;
            String smcu;
            String smcp;
          }
          Int smcconi = config.getPos("smc.con");
          smccon = config.get(smcconi);
          Int smcui = config.getPos("smc.u");
          smcu = config.get(smcui);
          Int smcpi = config.getPos("smc.p");
          smcp = config.get(smcpi);
        }
        checkStartSmcServer();
        checkStartMatrServer();
        checkStartEhServer();
        checkStartTaServer();
       }
      }
   }

   checkStartUpServer() {
    ifNotEmit(noUpd) {
      slots {
        Embedded:Update eupd;
      }
      if (Wifi.isConnected) {
        if (undef(eupd)) {
          eupd = Embedded:Update.new(self);
        }
      }
    }
   }

   checkStartTdServer() {
    ifNotEmit(noTds) {
      if (Wifi.isConnected) {
        if (undef(tdserver)) {
          tdserver = Embedded:Tds.new(myName, self);
          tdserver.start();
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
              //"smc not configed".print();
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

   checkStartMatrServer() {
     ifNotEmit(noMatr) {
      if (Wifi.isConnected) {
        if (undef(matrserver)) {
          matrserver = Embedded:MatrServer.new(self);
          matrserver.start();
        }
      }
    }
   }

   checkStartEhServer() {
     ifEmit(ehSvr) {
      if (Wifi.isConnected) {
        if (undef(ehserver)) {
          ehserver = Embedded:EHomeServer.new(self);
          ehserver.start();
        }
      }
    }
   }

   checkStartTaServer() {
     ifEmit(taSvr) {
      if (Wifi.isConnected) {
        if (undef(taserver)) {
          taserver = Embedded:TAServer.new(self);
          taserver.start();
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
        emit(cc) {
          """
          std::string aptype = BE_APTYPE;
          bevp_apType = new BEC_2_4_6_TextString(aptype);
          """
        }
      }
      if (TS.isEmpty(hiddenCode)) {
        emit(cc) {
          """
          std::string hiddenCode = BE_HIDECODE;
          bevp_hiddenCode = new BEC_2_4_6_TextString(hiddenCode);
          """
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
     Int shssidi = config.getPos("sh.ssid");
     ssid = config.get(shssidi);
     Int shseci = config.getPos("sh.sec");
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
       checkStartUpServer();
       checkStartTdServer();
       checkStartSmcServer();
       checkStartMatrServer();
       checkStartEhServer();
       checkStartTaServer();
     }
   }

   initPow() {
     "init pow".print();
     String pow = config.get(shpowi);
     if (TS.notEmpty(pow)) {
       Int powi = Int.new(pow);
       powi++;
       if (powi > 3) {
         powi = 3;
       }
       if (powi > 2 && resetByPow) {
         inResetByPow = true; //if was long running, must plug and unplug 3 times lt 30 secs each time
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
      emit(cc) {
          """
          std::string rbps = BE_RESETBYPOW;
          beq->bevl_rbps = new BEC_2_4_6_TextString(rbps);
          """
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
      nextPow = nowup + 30000;//30 secs
      clearPow();
      return(self);
     }
     if (nowup > endResetByPow) {
       endResetByPow = nowup + 1800000; //30 mins
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
                        List nrips = smcserver.nrips;
                        Int nrl = nrips.length;
                        Int fnripp;
                        for (Int nripp = 0;nripp < nrl, nripp++) {
                          String nrip = nrips[nripp];
                          if (TS.notEmpty(nrip) && nrip.begins(kdn)) {
                            rip = nrip.substring(nrip.find(",") + 1, nrip.length);
                            fnripp = nripp;
                            "got rip rips".print();
                            break;
                          }
                        }
                        if (TS.isEmpty(rip)) {
                          String rip = tdserver.getAddr(kdn);
                          if (rip == CNS.undefined) {
                            "no rip tds".print();
                          } else {
                            "got rip tds".print();
                            Int nrp = System:Random.getIntMax(smcserver.nrips.length);
                            smcserver.nrips.put(nrp, kdn + "," + rip);
                          }
                        }
                        if (TS.notEmpty(rip)) {
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
                            if (def(fnripp)) {
                              nrips[fnripp] = null;
                            }
                            tdserver.sayWants(kdn);
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
                //"fin doCmd tcp".print();
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
     ifEmit(ehSvr) {
       if (def(ehserver)) {
        ehserver.handleLoop();
       }
     }
     ifEmit(taSvr) {
       if (def(taserver)) {
        taserver.handleLoop();
       }
     }
     ifNotEmit(noUpd) {
       if (def(eupd)) {
         eupd.handleLoop();
       }
     }
     ifEmit (tcCon) {
     if (def(conserver)) {
       if (undef(concon)) {
        concon = conserver.checkGetClient();
       } else {
        unless (concon.connected) {
          concon = null;
        }
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
        nextRestart = nowup + 9000;// was 2000 / two sec
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
     if (cmdl.length > 0 && (cmdl[0].ends("p2") || cmdl[0].ends("p4") || cmdl[0].ends("p5") || cmdl[0].ends("p6"))) {
       return(doCmdlSec(channel, cmdl));
     }
     return(doCmdl(channel, cmdl));
   }

   hashIt(String it) String {
    String tohash = it;
    String hdone;
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
    return(hdone);
  }

   doCmdlSec(String channel, List cmdl) String {
     if (cmdl.length > 3) {
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
       if (cmdl[0].ends("p2")) {
        abeg = 3;
        tohash = cmdl[1] + "," + spw;
      } else {
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
       }
       hdone = hashIt(tohash);
       if (TS.notEmpty(hdone)) {
         //("hdone " + hdone).print();
         if (abeg > 3) {
          hdone = secTime(cmdl[1], hdone, cmdl[3]);
         }
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
      if (cmdl.length > 1) {
        String st = cmdl[1];
        if (st.isInteger) {
          Int sti = Int.new(st);
        }
      }
      if (undef(visnets) || undef(sti)) {
       var wifi = Embedded:Wifi.new();
       visnets = wifi.scanNetworks();
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
       if (cmdl.length > 5 && def(stateres)) {
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
          //"returning stateres".print();
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
        return("Error, must setup w/in 30 mins of power on.");
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
      if (inResetByPow || TS.isEmpty(ssid)) {
        "in resetByPow skip pass or ssid not yet set".print();
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
        Int shpassi = config.getPos("sh.pass");
        config.put(shpassi, newpass);
        pass = newpass;
      }

      String newspass = cmdl[3];
      if (TS.isEmpty(newspass)) {
        return("Error, new spass is required");
      }
      spass = newspass;
      Int shspassi = config.getPos("sh.spass");
      config.put(shspassi, spass);

      String newdid = cmdl[4];
      if (TS.notEmpty(did) && did.length == 16) {
        did = newdid;
        Int shdidi = config.getPos("sh.did");
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
        Int shssidi = config.getPos("sh.ssid");
        Int shseci = config.getPos("sh.sec");
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
         Int smcconi = config.getPos("smc.con");
         Int smcui = config.getPos("smc.u");
         Int smcpi = config.getPos("smc.p");
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
          String es = "";
          config.put(smcconi, es);
          config.put(smcui, es);
          config.put(smcpi, es);
        }
        }
        return("smcok");
     } elseIf (cmd == "brd") {
       ifNotEmit(noMatr) {
         if (def(matrserver)) {
           return(matrserver.handleCmdl(cmdl));
         }
        }
        return("unsupported");
     } elseIf (cmd == "ehcmd") {
       ifEmit(ehSvr) {
         if (def(ehserver)) {
           return(ehserver.handleCmdl(cmdl));
         }
        }
        return("unsupported");
     } elseIf (cmd == "tacmd") {
       ifEmit(taSvr) {
         if (def(taserver)) {
           return(taserver.handleCmdl(cmdl));
         }
        }
        return("unsupported");
     } elseIf (cmd == "reset") {
      reset();
      return("Device reset");//we look for this result, don't change
    } elseIf (cmd == "updnow") {
      ifEmit(noUpd) {
        return("updnow disabled");
      }
      ifNotEmit(noUpd) {
        if (def(eupd)) {
          eupd.handleUpdate();
          return("updnow attempting");
        } else {
          return("updnow failed undef");
        }
      }
     } elseIf (cmd == "maybesave") {
        config.maybeSave();
        needsGc = true;
        return("maybe saved");
     } elseIf (cmd == "sysupdate") {
        ifNotEmit(noUpd) {
          if (def(eupd)) {
           eupd.supurl = cmdl[2];
          }
        }
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
    String es = "";
    Int shpassi = config.getPos("sh.pass");
    config.put(shpassi, es);
    Int shssidi = config.getPos("sh.ssid");
    config.put(shssidi, es);
    Int shseci = config.getPos("sh.sec");
    config.put(shseci, es);
    Int shspassi = config.getPos("sh.spass");
    config.put(shspassi, es);
    Int shdidi = config.getPos("sh.did");
    config.put(shdidi, es);
    clearStates();
    ifNotEmit(noMatr) {
      if (def(matrserver)) {
        "clearing meps".print();
        matrserver.clearMeps();
        "meps cleared".print();
        matrserver.timeToDecom = true;
      }
    }
    ifEmit(ehSvr) {
      if (def(ehserver)) {
        ehserver.clearEhds();
      }
    }
    ifEmit(taSvr) {
      if (def(taserver)) {
        taserver.clearTads();
      }
    }
    ifNotEmit(noSmc) {
      Int smcconi = config.getPos("smc.con");
      config.put(smcconi, es);
      Int smcui = config.getPos("smc.u");
      config.put(smcui, es);
      Int smcpi = config.getPos("smc.p");
      config.put(smcpi, es);
    }
    needsFsRestart = true;
   }
   
}
