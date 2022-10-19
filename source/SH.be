// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:Files;
use Embedded:Config;
use Embedded:Aes as Crypt;
use Encode:Url as EU;

class Embedded:AppShell {
   
   main() {
     slots {
       auto app = Embedded:App.new();
       Int shpini;
       Int shrcodei;
       Int shpassi;
       Int shspassi;
       Int shssidi;
       Int shseci;
       Int shdidi;

       Int next3min = 0;
       Int next7min = 0;
       Int next13min = 0;
       Int nextday = 0;
       String slashn = "\n";
       String slashr = "\r";
       Config config = Config.new();
       String htmlHead;
       //List webPageL;
       Bool needsFsRestart = false;
       Bool needsRestart = false;
       Int nowup = Int.new();
       String did;
       String devType;
       String devCode;
       Int majVer;
       Int minVer;
       String readBuf = String.new();
     }
     app.plugin = self;

     "loading config".print();
     config.load();

     shpini = config.getPos("sh.pin");
     shrcodei = config.getPos("sh.rcode");
     shpassi = config.getPos("sh.pass");
     shspassi = config.getPos("sh.spass");
     shssidi = config.getPos("sh.ssid");
     shseci = config.getPos("sh.sec");
     shdidi = config.getPos("sh.did");

     app.uptime(nowup);
     next3min = nowup + 180000;
     next7min = nowup + 420000;
     next13min = nowup + 780000;
     nextday = nowup + 86400000;
     
     //"making webPage".print();
     htmlHead = String.new();
     htmlHead += "HTTP/1.1 200 OK\r\n";
     htmlHead += "Content-type:text/html\r\n";
     htmlHead += "Connection: close\r\n";
     htmlHead += "\r\n";
     /*String htmlStart = "<html>";
     String webPageHead = '''
          <head>
            <script>
            var ajaxSubmit = function(formid) {
              console.log("in ajaxSubmit");
              //if (false) {
              var form = document.getElementById(formid);
              var fs = "/";
              if (form.length > 0) {
              for (i = 0; i < form.length; i++) {
                 console.log("looping");
                 var qp;
                 if (i == 0) { qp = "?"; } else { qp = "&"; }
                 if (form.elements[i].name) {
                 fs = fs + qp;
                 fs = fs + encodeURIComponent(form.elements[i].name) + "=" + encodeURIComponent(form.elements[i].value);
               }
               }
               }
               document.getElementById('cmdres').value = '';
               document.getElementById('cmdshow').value = fs;
               console.log("submitting this");
               console.log(fs);
               var req;
               if (window.XMLHttpRequest) {
                 req = new XMLHttpRequest();
               } else if (window.ActiveXObject) {
                 try {
                   req = new ActiveXObject("Msxml2.XMLHTTP");
                 } 
                 catch (e) {
                   try {
                     req = new ActiveXObject("Microsoft.XMLHTTP");
                   } 
                   catch (e) {}
                 }
               }
               req.open('GET', fs, true);
               req.onreadystatechange = function(){
                   if (req.readyState != 4) return;
                   if (req.status != 200 && req.status != 304) {
                       //logmsg('HTTP error ' + req.status);
                       //location.reload();
                       return;
                   }
                   if (req.responseText != null && req.responseText != '') {
                     console.log(req.responseText);
                     //alert(req.responseText);
                     document.getElementById('cmdres').value = req.responseText;
                   }
               }
               req.send();
               console.log("submitted");
               //}
            }
            </script>
          </head>
          <body>
          ''';
     String htmlC1 = '''
     <form id="cmdformid" action="/" method="get" onsubmit="ajaxSubmit('cmdformid');return false;"><input type="hidden" name="cmdform" id="cmdform" value="cmdform"/>
     <br><label for="cmd">Your Command:</label><input type="text" id="cmd" name="cmd" size="64" maxLength="128"><br>
     <br><input type="submit" value="Send Command"></form>
     <form id="cmdresformid" action="/" method="get" onsubmit="ajaxSubmit('cmdresformid');return false;"><input type="hidden" name="cmdresform" id="cmdresform" value="cmdresform"/>
     <br><label for="cmdres">Command Results:</label><input type="text" id="cmdres" name="cmdres" size="64" maxLength="128"></form>
     <form id="cmdshowformid" action="/" method="get" onsubmit="ajaxSubmit('cmdshowformid');return false;"><input type="hidden" name="cmdshowform" id="cmdshowform" value="cmdshowform"/>
     <br><label for="cmdres">Command being Sent:</label><input type="text" id="cmdshow" name="cmdshow" size="64" maxLength="128"></form>
     ''';
     String htmlEnd = "</body></html>";
     webPageL = List.new();
     webPageL += htmlHead;
     webPageL += htmlStart;
     webPageL += webPageHead;
     webPageL += htmlC1;
     webPageL += htmlEnd;*/
     //"webpage made".print();
   }

   swInfoGet() String {
     fields {
       String swInfo;
     }
     if (undef(swInfo)) {
       swInfo = devType + " " + majVer + " " + minVer;
     }
     return(swInfo);
   }

   loadStates() {

   }

   configState(List cmdl) String {
     return("sh no impl");
   }

   doState(List cmdl) String {
     return("sh no impl");
   }
   
   clearStates() {

   }

   checkMakeIds() {
      fields {
        String pin;
      }

      pin = config.get(shpini);
      if (TS.isEmpty(pin) || pin.size != 16) {
        auto pinpart = System:Random.getString(8);
        pin = pinpart + pinpart;
        config.put(shpini, pin);
      }

      did = config.get(shdidi);
      if (TS.isEmpty(did)) {
        did = System:Random.getString(16);
        config.put(shdidi, did);
      }
   }

   loadPasses() {
      slots {
        String pass;
        String spass;
        String rcode;
      }

      pass = config.get(shpassi);
      spass = config.get(shspassi);
      rcode = config.get(shrcodei);

   }

   makeSwInfo() {
     devType = "shell";
     devCode = "gsh";
     majVer = 1;
     minVer = 2;
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
     app.wdtDisable();
     makeSwInfo();
     initRandom();
     checkMakeIds();
     loadPasses();

     self.swInfo.print();
     loadStates();
     "Device Id".print();
     did.print();
     "Pin".print();
     pin.print();
     self.swInfo.print();

     //System:Random.getIntMax(100).print();

     checkWifiAp();

     serserver = Embedded:SerServer.new();
     serserver.start();
     serserver.enableDebug();

     if (def(Wifi.localIP)) {
      ("Local ip " + Wifi.localIP).print();
      if (Wifi.up) {

        tcpserver = Embedded:TCPServer.new(5309);
        tcpserver.start();

        tweb = Embedded:TinyWeb.new();
        tweb.start();

        if (Wifi.isConnected) {

          mdserver = Embedded:Mdns.new();
          mdserver.name = "ym" + did;
          mdserver.service = "http";
          mdserver.port = 80;
          mdserver.protocol = "tcp";
          mdserver.start();

          checkUpd(1);

        }

      }

     }

   }
   
  checkWifiAp() {
     //"in checkWifiAp".print();
     unless (Wifi.up && Wifi.mode == "station") {
      startWifi();
      unless (Wifi.up) {
        if (TS.notEmpty(pin) && pin.size == 16) {
          String ssid = pin.substring(0, 8);
          String sec = pin.substring(8, 16);
          ssid = "yo_" + devCode + "_" + ssid;
          //("ssid from pin " + ssid).print();
          //("sec from pin " + sec).print();
          auto wifi = Embedded:Wifi.new();
          auto nets = wifi.scanNetworks();
          auto rand = System:Random.new();
          String finssid = ssid + "_" + rand.getString(4);
          while (nets.has(finssid)) {
            finssid = ssid + rand.getString(4);
          }
          Wifi.new(finssid, sec).startAp();
        }
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
       app.wdtDisable();
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
   }

   checkUpd(Int tries) {
     "in checkUpd".print();
     app.maybeGc();
     fields {
       String updHost;
       Int updPort;
       String updOut;
       String updCert;
     }
     if (undef(updHost)) {
       updHost = "hpprodev.bitsii.org";
       updPort = 14587;
       updOut = "GET /" + devType + majVer + "/ HTTP/1.1\r\n" + "Host: " + updHost + "\r\n" + "Connection: close\r\n\r\n";
       updCert = """
-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtqEIRx0r7kdVEvWruMyy
YzW1SVsi0skPADyV6dvTPyVdqdzHZ3xIAY+8mLvj+yOFIjgPqfGqDZWEUoMFhoQ1
HxNN3ex+ZBwHuVWiFYKGKm7j7O6eKdbExsTor1d7JuyVuWWBJPERJt0tdsmuyVoq
JxTxmdeOLQV59+q20iWJlwjNR3FbFSGAmSLPjlBRLjMecpEavgI1k2qmS1GPHx51
2BZZLwrIuECXEmjOl2eSEy8To4uG4/E6EMjbPJhTKcfFuuNiocXesiC88M2U9iIO
F1fuYdq2gJRNNtxGOhmgUEXG8j+e3Q4ENiTL4eAR/dic5AyGaEr/u2OQVaoSwZK7
1wIDAQAB
-----END PUBLIC KEY-----
""";
     }
     //"updOut".print();
     //updOut.print();
     String updLine = readBuf;
     updLine.clear();
     for (Int j = 0;j < tries;j++=) { //50
       //"try 0".print();
       app.wdtFeed();
       app.yield();
      Embedded:TCPClient client = Embedded:TCPClient.new(updHost, updPort);
      client.open();
      client.write(updOut);
      if (client.opened) {
        for (Int i = 0;i < 200;i++=) { //1000
          //"try 1".print();
          app.wdtFeed();
          app.yield();
          updLine = client.checkGetPayload(updLine, slashr);
          if (TS.notEmpty(updLine)) {
            //"updLine".print();
            //updLine.print();
            if (TS.notEmpty(updLine) && updLine.has("CurrentVer")) {
              break;
            }
          }
        }
      }
      if (TS.notEmpty(updLine) && updLine.has("CurrentVer")) {
        break;
      }
     }
     if (client.opened) { client.close(); }
     if (TS.notEmpty(updLine) && updLine.has("CurrentVer")) {
       //"gotit".print();
       //updLine.print();
       auto upds = updLine.split("|");
       String vjs = upds[1];
       String vms = upds[2];
       Int vj = Int.new(vjs);
       Int vm = Int.new(vms);
       ("ver info vj " + vj.toString() + " vm " + vm.toString()).print();
       if (vj > majVer || vm > minVer) {
         "should update".print();
         String upurl = upds[3];
         "upurl".print();
         upurl.print();
         auto eupd = Embedded:Update.new();
         eupd.signKey(updCert);
         eupd.updateFromUrl(upurl);
       }
    }
    "checkUpd done".print();
   }

   handleLoop() {
     app.wdtFeed();
     app.yield();
     app.wdtDisable();
     app.uptime(nowup);
     if (nowup > nextday) {
      nextday = nowup + 86400000;
      if (Wifi.isConnected) {
        checkUpd(3);
        return(self);
      }
     }
     if (nowup > next7min) {
      next7min = nowup + 420000;
      "maybe saving config".print();
      config.maybeSave();
      return(self);
     }
     if (nowup > next13min) {
      next13min = nowup + 780000;
      checkWifiUp();
      return(self);
     }
     if (nowup > next3min) {
      next3min = nowup + 180000;
      self.swInfo.print();
      return(self);
     }
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
     if (def(tweb)) {
      auto treq = tweb.checkGetRequest();
      if (def(treq)) {
        //"got treq".print();
        String qs = treq.checkGetQueryString(readBuf);
        if (TS.notEmpty(qs)) {
          if (qs == "/") {
            //"base qs sending webpage".print();
            //for (String part in webPageL) {
            //  treq.client.write(part);
            //}
          } elseIf (qs.begins("/?")) {
            auto qspso = qs.split("&");
            for (String qspsi in qspso) {
              if (TS.notEmpty(qspsi)) {
                //("got qspsi " + qspsi).print();
                auto qsps = qspsi.split("=");
                //gocha = cmd cannnnot be the first param, is it will have a /?
                if (qsps.size > 1 && def(qsps[0]) && qsps[0] == "cmd" && TS.notEmpty(qsps[1])) {
                  //("got cmd " + qsps[1]).print();
                  String cdec = EU.decode(qsps[1]);
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
     app.yield();
     if (cmdl.size < 1) {
       return("no cmd specified");
     }
     String cmd = cmdl[0];
     //("cmd is " + cmd).print();
     if (cmd == "dostate") {
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
        String stateres = doState(cmdl);
        return(stateres);
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
    } elseIf (cmd == "setrcode") {
      String newrcode = cmdl[1];
      unless (channel == "serial") {
        return("Error, only supported over Serial");
      }
      if (TS.isEmpty(newrcode)) {
       return("Error, newrcode is required");
      } else {
       config.put(shrcodei, newrcode);
       rcode = newrcode;
       return("rcode set");
      }
    } elseIf (cmd == "configstate") {
      unless (channel == "serial") {
        return("Error, only supported over Serial");
      }
      return(configState(cmdl));
    } elseIf (cmd == "setpass") {
      //"got setpasswithpin".print();
      String inpin = cmdl[1];
      String newpass = cmdl[2];
      if (TS.notEmpty(pin)) {
        if (TS.isEmpty(inpin)) {
          return("Error, pin was not sent");
        } elseIf (pin != inpin) {
          return("Error, pin is incorrect");
        }
      } else {
        return("Error, pin must be set");
      }
      if (TS.isEmpty(newpass)) {
       return("Error, new password is required");
      } else {
        if (TS.notEmpty(pass)) {
          return("Error, cannot set pass with pin once it has been set, repass instead");
        }
        pass = newpass;
        pass.print();
        config.put(shpassi, pass);
       return("Password set");
      }
     } elseIf (cmd == "reset") {
      String inrcode = cmdl[1];
      if (TS.notEmpty(rcode)) {
        if (TS.isEmpty(inrcode)) {
          return("Error, rcode was not sent");
        } elseIf (rcode != inrcode) {
          return("Error, rcode is incorrect");
        }
      } else {
        return("Error, rcode must be set");
      }
      config.put(shpassi, "");
      config.put(shssidi, "");
      config.put(shseci, "");
      config.put(shspassi, "");
      clearStates();
      return("Device reset");
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
           return("Error, initial password must be set with setpass");
         }
        inrcode = cmdl[3];
      if (TS.notEmpty(rcode)) {
        if (TS.isEmpty(inrcode)) {
          return("Error, rcode was not sent");
        } elseIf (rcode != inrcode) {
          return("Error, rcode is incorrect");
        }
      } else {
        return("Error, rcode must be set");
      }

        if (TS.isEmpty(newpass)) {
         return("Error, new password is required");
        } else {
         config.put(shpassi, newpass);
         pass = newpass;
         return("Password set");
        }
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
       //"got setwifi".print();
        ssid = cmdl[2];
        sec = cmdl[3];
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
     } elseIf (cmd == "clearstates") {
       //"got clearStates".print();
        clearStates();
        return("State cleared");
     } elseIf (cmd == "maybesave") {
        config.maybeSave();
        return("maybe saved");
     } elseIf (cmd == "restart") {
       //"got restart".print();
       needsFsRestart = true;
       return("Will restart soonish");
     } elseIf (cmd == "getdid") {
       return(did);
     } elseIf (cmd == "getdevtype") {
       return(devType);
     } elseIf (cmd == "getmajver") {
       return(majVer.toString());
     } elseIf (cmd == "getminver") {
       return(minVer.toString());
     } elseIf (cmd == "setdid") {
        String newdid = cmdl[2];
        if (TS.notEmpty(did) && did.size == 16) {
          did = newdid;
          config.put(shdidi, did);
          return("did now " + did);
        }
        return("need 16 char did");
     } elseIf (cmd == "setspass") {
        String newspass = cmdl[2];
        spass = newspass;
        spass.print();//to avoid write crash
        config.put(shspassi, spass);
        return("spass now " + spass);
     } else {
       return("unrecognized command");
     }
      return("Something's fishy");
   }
   
}
