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
       String supurl;
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
      }

      pass = config.get(shpassi);
      spass = config.get(shspassi);

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
          ssid = "yo_it_" + devCode + "_" + devType + "_" + ssid;
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

   sysupdate(String upurl) {
     "in update".print();
     "upurl".print();
     upurl.print();
     auto eupd = Embedded:Update.new();
     //eupd.signKey(updCert);
     eupd.updateFromUrl(upurl);
     "update done".print();
   }

   handleLoop() {
     app.wdtFeed();
     app.yield();
     app.wdtDisable();
     app.uptime(nowup);
     if (nowup > nextday) {
      nextday = nowup + 86400000;
      if (Wifi.isConnected) {
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
     if (TS.notEmpty(supurl)) {
       String upurl = supurl;
       supurl = null;
       sysupdate(upurl);
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
    } elseIf (cmd == "configstate") {
      unless (channel == "serial") {
        return("Error, only supported over Serial");
      }
      return(configState(cmdl));
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
        ssid = cmdl[4];
        sec = cmdl[5];
        if (cmdl[2] == "yrs") {
          needsFsRestart = true;
        }
        if (cmdl[3] == "hex") {
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
      clearStates();
      return("Device reset");
     } elseIf (cmd == "maybesave") {
        config.maybeSave();
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
   
}
