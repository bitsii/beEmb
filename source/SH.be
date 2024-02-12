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

class Embedded:AppShell {
   
   main() {
     fields {
       auto app = Embedded:App.new();
       Config config = Config.new();
       Int nowup = Int.new();
       String lastEventsRes;
       List controls = List.new();
       List loopers = List.new();
       List sxd = List.new();
       List sxdi = List.new();
       Embedded:TCPClient concon;
     }
     slots {
       Int shpini;
       Int shpassi;
       Int shspassi;
       Int shssidi;
       Int shseci;
       Int shdidi;
       Int shpowi;

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
       ifEmit(dynConf) {
         String fcdot = "fc.";
       }
       Bool needsFsRestart = false;
       Bool needsRestart = false;
       Bool justSetWifi = false;
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
       Int drift = 75;
     }
     ifNotEmit(noWeb) {
      slots {
        String htmlHead;
      }
     }
     app.plugin = self;

     "loading config".print();
     config.load();

     shpini = config.getPos("sh.pin");
     shpassi = config.getPos("sh.pass");
     shspassi = config.getPos("sh.spass");
     shssidi = config.getPos("sh.ssid");
     shseci = config.getPos("sh.sec");
     shdidi = config.getPos("sh.did");
     shpowi = config.getPos("sh.pow");

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
     if (def(lastEventsRes)) {
       return(lastEventsRes);
     }
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
        conPos++=;
      }
     }
     lastEventsRes = les;
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

      pin = config.get(shpini);
      if (TS.isEmpty(pin) || pin.size != 16) {
        emit(cc) {
          """
          std::string scode = BE_SCODE;
          beq->bevl_pinpart = new BEC_2_4_6_TextString(scode);
          """
        }
        if (TS.isEmpty(pinpart) || pinpart.size != 8) {
          String pinpart = System:Random.getString(8).lowerValue();
        }
        pin = pinpart + pinpart;
        config.put(shpini, pin);
      }

      did = config.get(shdidi);
      if (TS.isEmpty(did)) {
        did = System:Random.getString(16).lowerValue();
        config.put(shdidi, did);
      }
   }

   loadPasses() {
      slots {
        String pass;
        String spass;
      }

      pass = config.get(shpassi);
      spass = config.get(shspassi);

   }

   buildSwInfoIn() {
     if (TS.isEmpty(swSpec)) {
       swSpec = "1,q,p3,p2.Unspeced.5";
     }
     auto swl = swSpec.split(".");
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
     auto conl = controlSpec.split(".");
     Int i = 1;
     Int conPos = 0;
     while (i < conl.size) {
       if (conPos > 0) {
         controlDef += ",";
       }
       String conName = conl[i];
       i++=;
       String conArgs = conl[i];
       controls.put(conPos, buildControl(conPos, conName, conArgs));
       controlDef += controls.get(conPos).conType;
       conPos = conPos++;
       i++=;
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
     auto wifi = Embedded:Wifi.new();
     auto rhash = wifi.macAddress;

     Int i = 0;
     for (String net in wifi.scanNetworks()) {
       rhash += net;
       i++=;
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
        emit(cc) {
          """
          std::string tccon = BE_TCPCONSOLE;
          beq->bevl_tccon = new BEC_2_4_6_TextString(tccon);
          """
        }

        if (tccon == "on") {
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
            mdserver = Embedded:Mdns.new("CasNic" + did, "http", 80, "tcp");
            mdserver.start();
          }
        //}

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
        String apType; //I included, U unincluded, O open, for wifi sec
      }
      if (TS.isEmpty(apType)) {
        emit(cc) {
          """
          std::string aptype = BE_APTYPE;
          bevp_apType = new BEC_2_4_6_TextString(aptype);
          """
        }
      }
      if (TS.notEmpty(pin) && pin.size == 16) {
        if (apType == "U") {
          pinpt = pin.substring(0, 8);
          pinptp = "U";
        } else {
          String pinpt = pin.substring(0, 8);
          String pinptp = pinpt;
        }
        String sec = pin.substring(8, 16);
        String ssid = apType + "Casnic-";
        auto wifi = Embedded:Wifi.new();
        auto nets = wifi.scanNetworks();
        auto rand = System:Random.new();
        String finssidp = ssid + pinptp + "-" + devCode + "-" + rand.getIntMax(999);
        while (nets.has(finssidp)) {
          finssidp = ssid + pinptp + "-" + devCode + "-" + rand.getIntMax(999);
        }
        apSsid = ssid + pinpt + "-" + devCode + "-42";
        ("Device setup code " + pinpt).print();
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
       auto wifi = Embedded:Wifi.new();
       auto nets = wifi.scanNetworks();
       if (nets.has(ssid)) {
         "my ssid present".print();
         Wifi.new(ssid, sec).start();
       }
     }
     unless(needsFsRestart || needsRestart || justSetWifi) {
       if (Wifi.up && undef(tcpserver)) {
         needsNetworkInit = true;
       }
     }
   }

   sysupdate(String upurl) {
     ifNotEmit(noUpd) {
      "in update".print();
      "upurl".print();
      upurl.print();
      auto eupd = Embedded:Update.new();
      eupd.updateFromUrl(upurl);
      "update done".print();
     }
   }

   initPow() {
     "init pow".print();
     String pow = config.get(shpowi);
     if (TS.notEmpty(pow)) {
       Int powi = Int.new(pow);
       powi++=;
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
       emit(cc) {
          """
          std::string rbps = BE_RESETBYPOW;
          beq->bevl_rbps = new BEC_2_4_6_TextString(rbps);
          """
        }
        if (TS.notEmpty(rbps) && rbps == "on") {
          resetByPow = true;
        } else {
          resetByPow = false;
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
       endResetByPow = nowup + 1800000; //30 mins
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
            String scmdres = doCmd("serial", "", serpay);
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
     ifNotEmit(noWeb) {
      if (def(tweb)) {
        auto treq = tweb.checkGetRequest();
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
              auto qspso = qs.split("&");
              for (String qspsi in qspso) {
                if (TS.notEmpty(qspsi)) {
                  //("got qspsi " + qspsi).print();
                  auto qsps = qspsi.split("=");
                  //gocha = cmd cannnnot be the first param, is it will have a /?
                  if (qsps.size > 1 && def(qsps[0]) && TS.notEmpty(qsps[1])) {
                    if (qsps[0] == "cmd") {
                      //("got cmd " + qsps[1]).print();
                      String cdec = Encode:Url.decode(qsps[1]);
                      //("cdec " + cdec).print();
                      try {
                          String wcmdres = doCmd("web", "", cdec);
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
      auto preq = tcpserver.checkGetClient();
      if (def(preq)) {
        //"got preq".print();
        String ppay = preq.checkGetPayload(readBuf, slashn);
        if (TS.notEmpty(ppay)) {
            try {
                String pcmdres = doCmd("tcp", preq.remoteIp, ppay);
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
     while (looperI < loopers.size) {
       loopers.get(looperI).handleLoop();
       looperI++=;
     }
     ifNotEmit(noMdns) {
      if (def(mdserver)) {
        mdserver.update();
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

   doCmd(String channel, String origin, String cmdline) String {
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
     auto cmdl = cmdline.split(" ");
     //get rid of trailing newline NOW WE DOWN'T, ADD SOMETHING ON THE BACK
     //if (channel == "serial" && cmdl.size > 0) {
     //  cmdl.put(cmdl.size - 1, cmdl.get(cmdl.size - 1).swap("\n", ""));
     //}
     //if (channel == "tcp" && cmdl.size > 0) {
     //  cmdl.put(cmdl.size - 1, cmdl.get(cmdl.size - 1).swap("\r\n", ""));
     //}
     if (cmdl.size > 0 && cmdl[0].ends("p2") || cmdl[0].ends("p3")) {
       return(doCmdlSec(channel, origin, cmdl));
     }
     return(doCmdl(channel, origin, cmdl));
   }

   doCmdlSec(String channel, String origin, List cmdl) String {
     if (cmdl.size > 4) {
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
       if (cmdl[0].ends("3") && cmdl.size > 5) {
         Int abeg = 4;
       } else {
         abeg = 3;
       }
       if (TS.notEmpty(origin)) {
         //("got origin " + origin).print();
       } else {
         origin = "";
       }
       String tohash = cmdl[1] + "," + origin + "," + spw + ",";
       if (abeg == 4) {
         tohash += cmdl[3] += ",";
       }
       Int toc = cmdl.size - 1;
        String sp = " ";
        for (Int j = abeg.copy();j < toc;j++=) {
          tohash += cmdl[j] += sp;
        }
       //("tohash |" + tohash + "|").print();
       emit(cc) {
         """
      String lip = sha1(beq->bevl_tohash->bems_toCcString().c_str());
      std::string lips = std::string(lip.c_str());
      beq->bevl_hdone = new BEC_2_4_6_TextString(lips);
         """
       }
       if (TS.notEmpty(hdone)) {
         //("hdone " + hdone).print();
         if (abeg == 4) {
           hdone = secTime(hdone, cmdl[3]);
         }
         if (TS.notEmpty(cmdl[2]) && hdone == cmdl[2]) {
           ("hsec passed").print();
           cmdl.put(abeg + 1, spw);
           for (Int i = abeg.copy();i < cmdl.size;i++=) {
             cmdn += cmdl[i];
           }
         } else {
           ("hsec failed").print();
         }
       }
       return(doCmdl(channel, origin, cmdn));
     }
     return("nodice");
   }

   secTime(String hdone, String tesh) String {
     slots {
       Int lsec; //lsec last sent seconds since epoch
     }
     //tesh seconds since epoch passed in
     //drift seconds back that's ok
     Int teshi = app.strToInt(tesh);
     if (undef(lsec)) {
       teshi -= drift;
       lsec = teshi;
       return(hdone);
     }
     //new sent value must be > (last sent value - Xtolerance) (5secs? 10?)
     if (teshi > lsec) {
       //"passed secTime gt".print();
       teshi -= drift;
       lsec = teshi;
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
       auto wifi = Embedded:Wifi.new();
       visnets = wifi.scanNetworks();
     }
      if (cmdl.size > 1) {
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
        i++=;
        if (i > sti) {
          j++=;
          res += ":" += Encode:Hex.encode(net);
          if (j > 3) { break; }
        }
      }
      return(res);
   }
   
   doCmdl(String channel, String origin, List cmdl) String {
     app.maybeGc();
     app.wdtFeed();
     app.yield();
     needsGc = true;
     if (cmdl.size < 1) {
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
     } elseIf (cmd == "getlastevents") {
       stateres = getLastEvents(cmdl);
       return(stateres);
     } elseIf (cmd == "previsnets") {
       if (def(apSsid)) {
         return(getvisnets(cmdl));
       } else {
         return("on network nope");
       }
     } elseIf (cmd == "dostate" && cmdl.size > 3 && cmdl[3].begins("get")) {
       Int ctlPos = app.strToInt(cmdl[2]);
       stateres = doState(ctlPos, cmdl);
       return(stateres);
     } elseIf (cmd == "getstatexd") {
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
            xd = "undefined";
          }
          sxd[ctlPos] = xd;
       }
       return(xd);
     }
     if (cmd.begins("do") || cmd == "getcontroldef") {
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
        } else {
          if (def(controlDef)) {
            return(controlDef);
          } else {
            return("controldef,");
          }
        }
     }

     ifEmit(dynConf) {
        if (cmd == "setpin") {
          //"got setpin".print();
          String newpin = cmdl[1];
          unless (channel == "serial") {
            return("Error, only supported over Serial");
          }
          if (TS.isEmpty(newpin)) {
          return("Error, pin is required");
          } elseIf (newpin.isAlphaNum!) {
            return("Error, pin many only consist of letters and numbers");
          } elseIf (newpin.size != 16) {
            return("Error, pin must be 16 chars in length");
          } else {
          pin = newpin;
          pin.print();
          config.put(shpini, pin);
          return("Pin set");
          }
        }
     }

    if (cmd == "allset") {

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
      if (TS.notEmpty(did) && did.size == 16) {
        did = newdid;
        config.put(shdidi, did);
      } else {
        return("Error, newdid sized 16 required");
      }
      config.put(shpowi, "");
      return("allset done");

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
     } elseIf (cmd == "reset") {
      reset();
      return("Device reset");//we look for this result, don't change
    } elseIf (cmd == "putconfigs") {
      ifEmit(dynConf) {
        //String key = cmdl[3];
        //String value = cmdl[4];
        //if (TS.notEmpty(value)) {
        //
        //}
        if (cmdl[2] == "vhex") {
          Bool deHex = true;
        } else {
          deHex = false;
        }
        Int cmdle = cmdl.size - 1;
        for (Int k = 3;k < cmdle;k++=) {
          String key = cmdl[k];
          k++=;
          if (k < cmdle) {
            String value = cmdl[k];
          } else {
            value = null;
          }
          if (TS.notEmpty(key)) {
            if (key.begins(fcdot)) {
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
    needsFsRestart = true;
   }
   
}
