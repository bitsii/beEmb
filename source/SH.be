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
     }
     slots {
       Int shpini;
       Int shpassi;
       Int shspassi;
       Int shssidi;
       Int shseci;
       Int shdidi;

       Int nextUpdateCheck = 0;
       Int nextSwInfo = 0;
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
     nextSwInfo = nowup + 540000;
     nextMaybeSave = nowup + 105000;
     nextApCheck = nowup + 240000;//4 mins
     nextWifiCheck = nowup + 780000;//13 mins
     nextResetWindow = nowup + 570000;//9.5 mins
     
     //"making webPage".print();
     htmlHead = String.new();
     htmlHead += "HTTP/1.1 200 OK\r\n";
     htmlHead += "Content-type:text/html\r\n";
     htmlHead += "Connection: close\r\n";
     htmlHead += "\r\n";
     
   }

   sendWebPage(treq) {

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
     String d = ",";
     for (any control in controls) {
       Int le = control.lastEvent;
       Int conPos = control.conPos;
       if (def(le) && def(conPos)) {
         les += conPos += d += le += d;
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

     fields {
       Embedded:TinyWeb tweb;
       Embedded:TCPServer tcpserver;
       Embedded:SerServer serserver;
       Embedded:Mdns mdserver;
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
   
  checkWifiAp() {
     //"in checkWifiAp".print();
     unless (Wifi.up && Wifi.mode == "station") {
      startWifi();
      unless (Wifi.up) {
        if (TS.isEmpty(ssid) || readyForAp) {
          "start ap in checkWifiAp".print();
          initAp();
        }
      }
     }
   }

   initAp() {
      slots {
        String apSsid;
      }
      if (TS.notEmpty(pin) && pin.size == 16) {
        String pinpt = pin.substring(0, 8);
        String sec = pin.substring(8, 16);
        String ssid = "ICasnic-"; //I included, U unincluded, for wifi sec
        auto wifi = Embedded:Wifi.new();
        auto nets = wifi.scanNetworks();
        auto rand = System:Random.new();
        String finssid = ssid + pinpt + "-" + devCode + "-" + rand.getIntMax(999);
        while (nets.has(finssid)) {
          finssid = ssid + pinpt + "-" + devCode + "-" + rand.getIntMax(999);
        }
        apSsid = finssid;
        Wifi.new(finssid, sec).startAp();
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
    "checking if wifi up".print();
    unless (Wifi.isConnected || TS.isEmpty(ssid)) {
       "configured but not up".print();
       auto wifi = Embedded:Wifi.new();
       auto nets = wifi.scanNetworks();
       if (nets.has(ssid)) {
         "my ssid looks to be present, restarting".print();
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
        "maybe saving config".print();
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
      nextWifiCheck = nowup + 780000;//13 mins
      checkWifiUp();
      return(self);
     }
     if (nowup > nextResetWindow) {
      nextResetWindow = nowup + 570000;//9.5 mins
      if (inReset) {
        inReset = false;
        "leaving reset window".print();
      }
      if (justStarted) {
        justStarted = false;
        inReset = true;
        "entering reset window".print();
      }
      return(self);
     }
     if (nowup > nextSwInfo) {
      nextSwInfo = nowup + 540000;
      swInfo.print();
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
        "preding serpay".print();
        String serpay = serserver.checkGetPayload(readBuf, slashn);
      }
      if (TS.notEmpty(serpay)) {
        try {
            "doing serpay".print();
            String cmdres = doCmd("serial", serpay);
            if (TS.isEmpty(cmdres)) {
              "cmdres empty".print();
            } else {
              ("cmdres " + cmdres).print();
            }
          } catch (any dce) {
            "error handling command".print();
            dce.print();
          }
          "serpay returning".print();
          //app.yield();
          "now".print();
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
                          cmdres = doCmd("web", cdec);
                          treq.client.write(htmlHead); //ok headers
                          if (TS.isEmpty(cmdres)) {
                            treq.client.write("cmdres empty");
                          } else {
                            treq.client.write(cmdres);
                          }
                        } catch (dce) {
                          "error handling command".print();
                          dce.print();
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
     if (def(mdserver)) {
       mdserver.update();
     }
     if (needsRestart) {
       needsRestart = false;
       "restarting because needsRestart".print();
        Wifi.stop();
        Wifi.clearAll();
        app.restart();
     }
     if (needsFsRestart) {
       needsFsRestart = false;
       "maybe saving config".print();
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
     ("cmd channel follows").print();
     channel.print();
     ("cmdline follows").print();
     cmdline.print();
     auto cmdl = cmdline.split(" ");
     //get rid of trailing newline NOW WE DOWN'T, ADD SOMETHING ON THE BACK
     //if (channel == "serial" && cmdl.size > 0) {
     //  cmdl.put(cmdl.size - 1, cmdl.get(cmdl.size - 1).swap("\n", ""));
     //}
     //if (channel == "tcp" && cmdl.size > 0) {
     //  cmdl.put(cmdl.size - 1, cmdl.get(cmdl.size - 1).swap("\r\n", ""));
     //}
     return(doCmdl(channel, cmdl));
   }
   
   doCmdl(String channel, List cmdl) String {
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
     }
     if (cmd == "dostate" || cmd == "getcontroldef" || cmd == "getlastevents") {
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
        } elseIf (cmd == "getlastevents") {
          stateres = getLastEvents(cmdl);
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
        if (cmdl[2] == "hex") {
          if (TS.notEmpty(key)) {
            key = Encode:Hex.decode(key);
          }
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
