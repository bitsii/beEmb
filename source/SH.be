// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

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
       Bool needsStateUp = false;
       Bool needsStateUpSoon = false;
     }
     slots {
       Int shpini;
       Int shpassi;
       Int shspassi;
       Int shssidi;
       Int shseci;
       Int shdidi;

       Int zero = 0;
       Int nextUpdateCheck = 0;
       Int nextMq = 0;
       Int nextSwInfo = 0;
       Int nextRestart = 0;
       Int nextMaybeSave = 0;
       Int nextApCheck = 0;
       Int nextWifiCheck = 0;
       Int nextResetWindow = 0;
       String slashn = "\n";
       String slashr = "\r";
       String htmlHead;
       Bool needsFsRestart = false;
       Bool needsRestart = false;
       String did;
       String swSpec;
       String devCode;
       Int version;
       String swInfo;
       Bool justStarted = true;
       Bool inReset = false;
       String readBuf = String.new();
       String supurl;
       String controlSpec;
       String controlDef;
       List controls = List.new();
       Bool needsNetworkInit = true;
       Bool readyForAp = false;
       Bool needsBuildControls = true;
       Bool needsLoadStates = true;
       Bool needsGc = false;
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

     app.uptime(nowup);
     nextUpdateCheck = nowup + 60000;
     nextMq = nowup + 11000;
     nextSwInfo = nowup + 540000;
     nextMaybeSave = nowup + 105000;
     nextApCheck = nowup + 240000;//4 mins
     nextWifiCheck = nowup + 300000;//13 mins
     nextResetWindow = nowup + 570000;//9.5 mins
     
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

   loadStates() {
     for (any control in controls) {
       control.loadStates();
     }
   }

   doState(List cmdl) String {
     //Int ctlPos = Int.new(cmdl[2]);
     Int ctlPos = app.strToInt(cmdl[2]);
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
      for (any control in controls) {
        String conName = control.conName;
        Int le = control.lastEvent;
        Int conPos = control.conPos;
        if (def(le) && def(conPos)) {
          les += conName += d += conPos += d += le += cd;
        }
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
      fields {
        String pin;
      }

      pin = config.get(shpini);
      if (TS.isEmpty(pin) || pin.size != 16) {
        auto pinpart = System:Random.getString(8).lowerValue();
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

   buildSwInfo() {
     if (TS.isEmpty(swSpec)) {
       swSpec = "0.gsh.4";
     }
     auto swl = swSpec.split(".");
     devCode = swl[1];
     //version = Int.new(swl[2]);
     version = app.strToInt(swl[2]);
     swInfo = devCode + " " + version;
   }

   buildControl(Int conPos, String conName, String conArgs) {
     //sh no impl
     "buildControl called in SH".print();
     return(null);
   }

   buildControls() {
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
       controlDef += conName;
       i++=;
       String conArgs = conl[i];
       controls.put(conPos, buildControl(conPos, conName, conArgs));
       conPos = conPos++;
       i++=;
     }
     ("controlDef " + controlDef).print();
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
       fields {
         Embedded:TinyWeb tweb;
       }
     }
     ifNotEmit(noSer) {
       fields {
        Embedded:SerServer serserver;
       }
     }
     ifNotEmit(noMdns) {
       fields {
        Embedded:Mdns mdserver;
       }
     }
     ifNotEmit(noMqtt) {
       fields {
        Embedded:Mqtt mqtt;
       }
     }
     fields {
       Embedded:TCPServer tcpserver;
     }

     app.wdtFeed();
     app.yield();
     //app.wdtDisable();
     app.wdtEnable(0);
     buildSwInfo();
     initRandom();
     checkMakeIds();
     loadPasses();

     swInfo.print();
     "Device Id".print();
     did.print();
     "Pin".print();
     pin.print();
     swInfo.print();

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

        ifNotEmit(noWeb) {
         tweb = Embedded:TinyWeb.new();
         tweb.start();
        }

        if (Wifi.isConnected) {
          ifNotEmit(noMdns) {
            mdserver = Embedded:Mdns.new();
            mdserver.name = "CasNic" + did;
            mdserver.service = "http";
            mdserver.port = 80;
            mdserver.protocol = "tcp";
            mdserver.start();
          }

        }

       }
      }
   }

   initMq() {
     ifNotEmit(noMqtt) {
       if (def(mqtt)) {
         auto oldmqtt = mqtt;
         mqtt = null;
         oldmqtt.close();
       }
       if (Wifi.isConnected) {
        mqtt = Embedded:Mqtt.new("192.168.1.124", "ha", "hapass");
        if (mqtt.open()) {
          mqtt.subscribeAsync("homeassistant/status");
          //mqtt.subscribeAsync("/test");
          mqConfUp(true);
          needsGc = true;
        } else {
          oldmqtt = mqtt;
          mqtt = null;
          oldmqtt.close();
        }
       }
     }
   }

   mqConfUp(Bool doSubs) {
     ifNotEmit(noMqtt) {
      "mqConfUp".print();
      mqtt.minAsyncCapacity = controls.size;
      unless (mqtt.hasAsyncCapacity(controls.size)) {
        "mqtt conf not enough space".print();
        return(self);
      }
      //String tpp = "homeassistant/switch/" + did + "-" + i;
      //Map cf = Maps.from("name", conf["name"], "command_topic", tpp + "/set", "state_topic", tpp + "/state", "unique_id", did + "-" + i);
      //tpp = "homeassistant/light/" + did + "-" + i;
      //cf = Maps.from("name", conf["name"], "command_topic", tpp + "/set", "state_topic", tpp + "/state", "unique_id", did + "-" + i, "schema", "json", "brightness", true, "brightness_scale", 255);

      Int keyi = config.getPos("dname");
      String dname = config.get(keyi);
      if (TS.isEmpty(dname)) {
        dname = "CasNic Device";
      }

      any ctl;
      String conName;
      Int conPoss;
      String tpp;
      String cf;
      String pt;
      for (ctl in controls) {
        conName = ctl.conName;
        conPoss = ctl.conPos.toString();
        if (conName == "sw") {
          tpp = "homeassistant/switch/" + did + "-" + conPoss;
          pt = tpp + "/config";
          cf = "{ \"name\": \"" += dname += " " += conPoss += "\", \"command_topic\": \"" += tpp += "/set\", \"state_topic\": \"" += tpp += "/state\", \"unique_id\": \"" += did += "-" += conPoss += "\" }";
          if (doSubs) {
            mqtt.subscribeAsync(tpp += "/set");
          }
        } elseIf (conName == "dim") {
          tpp = "homeassistant/light/" + did + "-" + conPoss;
          pt = tpp + "/config";
          cf = "{ \"name\": \"" += dname += " " += conPoss += "\", \"command_topic\": \"" += tpp += "/set\", \"state_topic\": \"" += tpp += "/state\", \"unique_id\": \"" += did += "-" += conPoss += "\", \"schema\": \"json\", \"brightness\": true, \"brightness_scale\": 255 }";
          if (doSubs) {
            mqtt.subscribeAsync(tpp += "/set");
          }
        }
        if (TS.notEmpty(pt) && TS.notEmpty(cf)) {
          cf.print();
          mqtt.publishAsync(pt, cf);
        }
      }
      //mqStateUp();
      needsStateUpSoon = true;
    }
   }

   mqStateUp() {
     ifNotEmit(noMqtt) {
      "mqStateUp".print();
      unless (mqtt.hasAsyncCapacity(controls.size)) {
        "mqtt state not enough space".print();
        return(self);
      }

      any ctl;
      String conName;
      Int conPoss;
      String tpp;
      String cf;
      String pt;
      for (ctl in controls) {
        conName = ctl.conName;
        conPoss = ctl.conPos.toString();
        if (conName == "sw") {
          tpp = "homeassistant/switch/" + did + "-" + conPoss;
          pt = tpp + "/state";
          if (TS.notEmpty(ctl.sw)) {
            cf = ctl.sw.upper();
          } else {
            cf = "OFF";
          }
        } elseIf (conName == "dim") {
          tpp = "homeassistant/light/" + did + "-" + conPoss;
          pt = tpp + "/state";
          cf = "{ \"state\": \"";
          if (TS.notEmpty(ctl.sw)) {
            cf += ctl.sw.upper();
          } else {
            cf += "OFF";
          }
          cf += "\"";
          if (TS.notEmpty(ctl.lvl)) {
            Int inlvli = Int.new(ctl.lvl);
            inlvli = 255 - inlvli;//255 - x = y; y + x = 255;255 - y = x
            cf += ", \"brightness\": " += inlvli.toString();
          }
          cf += " }";
        }
        if (TS.notEmpty(pt) && TS.notEmpty(cf)) {
          cf.print();
          mqtt.publishAsync(pt, cf);
        }
      }
     }
   }
   
  checkWifiAp() {
     //"in checkWifiAp".print();
     unless (Wifi.up && Wifi.mode == "station") {
      startWifi();
      unless (Wifi.up) {
        if (TS.isEmpty(ssid) || readyForAp) {
          //"start ap in checkWifiAp".print();
          initAp();
        }
      }
     }
   }

   initAp() {
      slots {
        String apSsid;
        String apType = "O"; //I included, U unincluded, O open, for wifi sec
      }
      if (TS.notEmpty(pin) && pin.size == 16) {
        String pinpt = pin.substring(0, 8);
        String sec = pin.substring(8, 16);
        String ssid = apType + "Casnic-";
        auto wifi = Embedded:Wifi.new();
        auto nets = wifi.scanNetworks();
        auto rand = System:Random.new();
        String finssid = ssid + pinpt + "-" + devCode + "-" + rand.getIntMax(999);
        while (nets.has(finssid)) {
          finssid = ssid + pinpt + "-" + devCode + "-" + rand.getIntMax(999);
        }
        apSsid = finssid;
        if (apType == "O") {
          Wifi.new(finssid, null).startAp();
        } else {
          Wifi.new(finssid, sec).startAp();
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
       ("ssid " + ssid + " sec " + sec).print();
       app.wdtFeed();
       app.yield();
       //app.wdtDisable();
       Wifi.new(ssid, sec).start();
     }
   }
   
   checkWifiUp() {
    //"checking if wifi up".print();
    unless (Wifi.isConnected || TS.isEmpty(ssid)) {
       "wifi configured but not up".print();
       auto wifi = Embedded:Wifi.new();
       auto nets = wifi.scanNetworks();
       if (nets.has(ssid)) {
         "my ssid present, restarting".print();
         needsFsRestart = true;
       }
     }
     unless(needsFsRestart) {
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
      //eupd.signKey(updCert);
      eupd.updateFromUrl(upurl);
      "update done".print();
     }
   }

   handleLoop() {
     app.wdtFeed();
     app.yield();
     //app.wdtDisable();
     app.uptime(nowup);
     if (needsNetworkInit) {
       needsNetworkInit = false;
       networkInit();
       return(self);
     }
     if (needsBuildControls) {
       needsBuildControls = false;
       buildControls();
       return(self);
     }
     if (needsLoadStates) {
       needsLoadStates = false;
       loadStates();
       needsStateUp = false;
       return(self);
     }
     if (needsGc) {
       needsGc = false;
       app.maybeGc();
       return(self);
     }
     if (nowup > nextMaybeSave) {
      nextMaybeSave = nowup + 105000;
      if (config.changed) {
        "maybeSave config".print();
        config.maybeSave();
      }
      needsGc = true;
      return(self);
     }
     if (nowup > nextApCheck) {
      nextApCheck = nowup + 240000;//4 mins
      unless (readyForAp) {
        readyForAp = true;
        unless (Wifi.up) {
          needsNetworkInit = true;
        }
      }
      return(self);
     }
     if (nowup > nextWifiCheck) {
      nextWifiCheck = nowup + 300000;//5 mins
      checkWifiUp();
      return(self);
     }
     if (nowup > nextResetWindow) {
      nextResetWindow = nowup + 570000;//9.5 mins
      if (inReset) {
        inReset = false;
        "leaving reset".print();
      }
      if (justStarted) {
        justStarted = false;
        inReset = true;
        "entering reset".print();
      }
      return(self);
     }
     if (nowup > nextSwInfo) {
      nextSwInfo = nowup + 540000;
      swInfo.print();
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
     if (nowup > nextMq) {
      nextMq = nowup + 11000;
      ifNotEmit(noMqtt) {
        unless (def(mqtt) && mqtt.isOpen) {
          initMq();
        } else {
          //mqtt.publish("/test", "test from sh pub");
          if (needsStateUpSoon) {
            needsStateUpSoon = false;
            needsStateUp = true;
          }
        }
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
     ifNotEmit(noMqtt) {
      if (def(mqtt)) {
        if (mqtt.handleAsync(self)) {
          needsGc = true;
          return(self);
        }
      }
     }
     if (needsStateUp) {
      needsStateUp = false;
      ifNotEmit(noMqtt) {
        if (def(mqtt)) {
          mqStateUp();
        }
        needsGc = true;
      }
      return(self);
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

   handleMqtt(String topic, String payload) {
    "got mqtt".print();
      if (TS.notEmpty(topic) && TS.notEmpty(payload)) {
        ("Topic: " + topic + " Payload: " + payload).print();
        //Topic:homeassistant/status;Payload:online;
        if (topic == "homeassistant/status" && payload == "online") {
          mqConfUp(false);
        }
        needsGc = true;
      } else {
        "Topic or Payload Empty".print();
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
     if (cmdl.size > 0 && cmdl[0] == "sp1" || cmdl[0] == "ap1") {
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
       if (cmdl[0] == "sp1") {
         spw = spass;
       } elseIf (cmdl[0] == "ap1") {
         spw = pass;
       } else {
         ("unknown secsceme " + cmdl[0]).print();
       }
       if (TS.notEmpty(origin)) {
         //("got origin " + origin).print();
       } else {
         origin = "";
       }
       String tohash = cmdl[1] + "," + origin + "," + spw;
       //"tohash follows".print();
       //tohash.print();
       emit(cc) {
         """
      String lip = sha1(beq->bevl_tohash->bems_toCcString().c_str());
      std::string lips = std::string(lip.c_str());
      beq->bevl_hdone = new BEC_2_4_6_TextString(lips);
         """
       }
       if (TS.notEmpty(hdone)) {
         //("hdone " + hdone).print();
         if (TS.notEmpty(cmdl[2]) && hdone == cmdl[2]) {
           ("hsec passed").print();
           cmdl[4] = spw;
           for (Int i = 3;i < cmdl.size;i++=) {
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
     }
     if (cmd == "dostate" || cmd == "getcontroldef") {
        //"got dostate".print();
        //state password check
        if (TS.isEmpty(spass)) {
          return("State Password Must Be Set");
        }
        inpass = cmdl[1];
        if (TS.isEmpty(inpass)) {
          return("State password must be provided");
        }
        if (inpass != spass) {
          return("State Password Incorrect");
        }
        if (cmd == "dostate") {
          String stateres = doState(cmdl);
          return(stateres);
        } else {
          if (def(controlDef)) {
            return(controlDef);
          } else {
            return("controldef,");
          }
        }
     }

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
    } elseIf (cmd == "allset") {

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
      if (TS.notEmpty(pass)) {
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

      return("allset done");

     } elseIf (cmd == "repass") {
       //"got setpasswithpass".print();
        String inpass = cmdl[1];
        newpass = cmdl[2];
         if (TS.notEmpty(pass)) {
           if (TS.isEmpty(inpass)) {
             return("Error, pass was not sent");
           } elseIf (pass != inpass) {
             return("Error, pass is incorrect");
           }
         } else {
           return("Error, initial password must be set");
         }

        if (TS.isEmpty(newpass)) {
         return("Error, new password is required");
        } else {
         config.put(shpassi, newpass);
         pass = newpass;
         return("Password set");
        }
      } elseIf (cmd == "resetbypin") {
        unless (inReset) {
          return("Error, not in reset window");
        }
        inpin = cmdl[1];
        if (TS.notEmpty(pin)) {
          if (TS.isEmpty(inpin)) {
            return("Error, pin was not sent");
          } elseIf (pin != inpin) {
            return("Error, pin is incorrect");
          }
        } else {
          return("Error, pin must be set");
        }
        config.put(shpassi, "");
        config.put(shssidi, "");
        config.put(shseci, "");
        config.put(shspassi, "");
        config.put(shdidi, "");
        clearStates();
        needsFsRestart = true;
        return("Device reset");
     }

     //password check
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

     if (cmd == "setwifi") {
        ssid = cmdl[3];
        sec = cmdl[4];
        if (cmdl[2] == "hex") {
          if (TS.notEmpty(ssid)) {
            ssid = Encode:Hex.decode(ssid);
          }
          if (TS.notEmpty(sec)) {
            sec = Encode:Hex.decode(sec);
          }
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
          return("Wifi Setup Written, restart to activate");
        } else {
          ("ssid missing").print();
          config.put(shssidi, "");
          config.put(shseci, "");
          return("Wifi Setup cleared, restart to activate");
        }
     } elseIf (cmd == "reset") {
      config.put(shpassi, "");
      config.put(shssidi, "");
      config.put(shseci, "");
      config.put(shspassi, "");
      config.put(shdidi, "");
      clearStates();
      needsFsRestart = true;
      return("Device reset");//we look for this result, don't change
    } elseIf (cmd == "putconfig") {
        String key = cmdl[3];
        String value = cmdl[4];
        if (cmdl[2] == "vhex") {
          if (TS.notEmpty(value)) {
            value = Encode:Hex.decode(value);
          }
        }
        if (TS.notEmpty(key)) {
          Int keyi = config.getPos(key);
          if (TS.isEmpty(value)) {
            config.put(keyi, "");
          } else {
            config.put(keyi, value);
          }
        }
        return("config set");
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
     } elseIf (cmd == "getswinfo") {
       return(swInfo);
     } else {
       return("unrecognized command");
     }
      return("Something's fishy");
   }
   
}
