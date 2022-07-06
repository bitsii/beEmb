// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:Files;
use Encode:Hex as Hex;
use Embedded:Aes as Crypt;

class Embedded:LedApp {
   
   main() {
     fields {
       auto app = Embedded:App.new();
       auto webserver = Embedded:WebServer.new(app);
       auto serserver = Embedded:SerServer.new();
       auto delay = 2; //ms
       String ssidf = "/lawifissid.txt";
       String secf = "/lawifisec.txt";
       String passf = "/ladevpass.txt";
       String statef = "/lastate.txt";
       Int swpin = 2;
       //String udpRes;
       Int tick = 0;
       Files files = Files.new();
       auto upcheckFrequency = 1200; //20 mins
       auto upcheckCount = 0;
       auto rpsClearFrequency = 20; //20 secs
       auto rpsClearCount = 0;
       Set rpsCheck = Set.new();
       auto lastSse = 0;
       auto lastSseSlush = 10;
       List webPageL;
       Bool needsRestart = false;
     }
     app.plugin = self;
     "opening files".print();
     files.open();
     
     "making webPage".print();
     String htmlStart = "<html>";
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
                     alert(req.responseText);
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
     ''';
     String htmlEnd = "</body></html>";
     webPageL = List.new();
     webPageL += htmlStart;
     webPageL += webPageHead;
     webPageL += htmlC1;
     webPageL += htmlEnd;
     "webpage made".print();
   }
   
   checkState() {
     if (files.exists(statef)) {
       String payload = files.read(statef);
       if (TS.notEmpty(payload)) {
         doState(payload);
       }
     } else {
       app.digitalWriteHigh(swpin);
     }
   }
   
   doState(String state) String {
     if (TS.notEmpty(state)) {
       if (state == "on") {
       "should turn on".print();
       app.digitalWriteLow(swpin);
       files.write(statef, "on");
       } elseIf (state == "off") {
         "should turn OFF".print();
         app.digitalWriteHigh(swpin);
         files.write(statef, "off");
       } elseIf (state == "check") {
         if (files.exists(statef)) {
           state = files.read(statef);
           if (TS.isEmpty(state)) {
             state = "bad";
           }
         } else {
           state = "unknown";
         }
       } else {
         state = "invalid";
       }
     } else {
       files.delete(statef);
       state = "unset";
     }
     return(state);
   }
   
   startLoop() {
     "in startLoop LedApp".print();
     app.pinModeOutput(swpin);
     serserver.start();
     checkWifiAp();
     if (def(Wifi.localIP)) {
      ("Local ip " + Wifi.localIP).print();
      "starting ws".print();
      webserver.start();
     }
     checkState();
   }
   
  checkWifiAp() {
     "in checkWifiAp".print();
     unless (Wifi.up && Wifi.mode == "station") {
      "trying startwifi".print();
      startWifi();
      unless (Wifi.up) {
        "starting ap".print();
        Wifi.new("EspAp2", "goodstuf").startAp();
      }
     }
   }
   
   startWifi() {
     "in startWifi".print();
     if (files.exists(ssidf)) {
      String ssid = files.read(ssidf);
      if (TS.notEmpty(ssid)) {
        ("ssid " + ssid).print();
      }
     }
     if (files.exists(secf)) {
      String sec = files.read(secf);
      if (TS.notEmpty(sec)) {
        ("sec " + sec).print();
      }
     } else {
       sec = "";
     }
     if (TS.notEmpty(ssid)) {
       "setting up wifi".print();
       Wifi.new(ssid, sec).start();
       "done".print();
     }
   }
   
   maybeCheckWifiUp() {
     //"may checking wifi up".print();
     upcheckCount++=;
     if (upcheckCount > upcheckFrequency) {
       "checking wifi up".print();
       upcheckCount = 0;
       unless (Wifi.isConnected) {
         needsRestart = true;
       }
     }
   }
   
   maybeClearRps() {
     //"may checking clearrps".print();
     rpsClearCount++=;
     if (rpsClearCount > rpsClearFrequency) {
       //"clear rps".print();
       rpsClearCount = 0;
       rpsCheck = Set.new();
     }
   }
   
   handleLoop() {
     tick++=;
     if (tick > 30000) {
      //it's been a minute
      tick = 0;
      "reset tick".print();
     }
     if (tick % 500 == 0) {
      //it's been a second
      maybeCheckWifiUp();
      maybeClearRps();
     }
     auto serpay = serserver.checkGetPayload("\n");
     if (TS.notEmpty(serpay)) {
       try {
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
     }
     webserver.checkHandleWeb();
     if (needsRestart) {
       needsRestart = false;
       "restarting because needsRestart".print();
        Wifi.stop();
        Wifi.clearAll();
        app.restart();
     }
     app.delay(delay);
   }
   
   doCmd(String channel, String cmdline) String {
     if (TS.isEmpty(cmdline)) {
       "cmdline empty".print();
       return("cmdline empty");
     }
     //check max length and num of spaces
     cmdline = cmdline.swap("\n", "");
     ("cmdline is " + cmdline).print();
     auto cmdl = cmdline.split(" ");
     Map cmds = Map.new();
     for (String cmdp in cmdl) {
       if (cmdp.has("=")) {
         auto p = cmdp.split("=");
         cmds.put(p[0], p[1]);
       } else {
         cmds.put(cmdp, null);
       }
     } 
     return(doCmds(channel, cmds));
   }
   
   doCmds(String channel, Map cmds) String {
     if (TS.isEmpty(channel)) {
       "channel empty".print();
       return("channel empty");
     }
     if (cmds.has("hexed")) {
       Map ncmds = Map.new();
       for (auto kv in cmds) {
         if (def(kv.value)) {
           ncmds.put(kv.key, Hex.decode(kv.value));
         } else {
           ncmds.put(kv.key, null);
         }
       }
       cmds = ncmds;
     }
     if (cmds.has("cmd")) {
       String cmd = cmds["cmd"];
     } else {
       "no cmd".print();
       return("no cmd specified");
     }
     ("cmd is " + cmd).print();
     unless (cmd == "setpass") {
       if (files.exists(passf)) {
         String inpass = cmds["pass"];
         if (TS.isEmpty(inpass)) {
           return("Device password must be provided");
         }
         pass = files.read(passf);
         if (TS.isEmpty(pass)) {
          return("Device Password Must Be Set");
         }
         if (inpass != pass) {
           return("Device Password Incorrect");
         }
       } else {
         return("Device Password Must Be Set");
       } 
     }
     if (cmd == "setwifi") {
       "got setwifi".print();
        String ssid = cmds["ssid"];
        String sec = cmds["sec"];
        if (TS.notEmpty(ssid)) {
          ("got ssid " + ssid).print();
          files.write(ssidf, ssid);
          if (TS.notEmpty(sec)) {
            ("got sec " + sec).print();
            files.write(secf, sec);
          } else {
            ("sec missing").print();
            files.delete(secf);
          }
          needsRestart = true;
          return("Wifi Setup Complete");
        } else {
          ("ssid missing").print();
          files.delete(ssidf);
          files.delete(secf);
          needsRestart = true;
          return("Wifi Setup cleared");
        }
     } elseIf (cmd == "state") {
       "got setstate".print();
        String state = cmds["state"];
        String stateres = doState(state);
        return("State now " + stateres);
     } elseIf (cmd == "restart") {
       "got restart".print();
       needsRestart = true;
     } elseIf (cmd == "setpass") {
       "got setpass".print();
        String oldpass = cmds["oldpass"];
        String newpass = cmds["newpass"];
        unless (channel == "serial") {
          if (files.exists(passf)) {
           String pass = files.read(passf);
           if (TS.notEmpty(pass)) {
             ("currpass " + pass).print();
             if (TS.isEmpty(oldpass)) {
               return("Error, password is set but oldpass was not sent");
             } elseIf (pass != oldpass) {
               return("Error, oldpass is incorrect");
             }
           }
          }
        }
        if (TS.isEmpty(newpass)) {
         return("Password cleared");
        } else {
         files.write(passf, newpass);
         return("Password set");
        }
     } else {
       return("unrecognized command");
     }
      return("Something's fishy");
   }
   
    handleWeb(request) {
     "in ledapp handleweb".print();
     "getting params".print();
      String cmdform = request.getParameter("cmdform");
      "checking forms".print();
      if (TS.notEmpty(cmdform) && cmdform == "cmdform") {
        "got cmdform".print();
        String cmd = request.getParameter("cmd");
        if (TS.notEmpty(cmd)) {
          ("cmd was: " + cmd).print();
        } else {
          "cmd missing".print();
          request.outputContent = "cmd missing";
          return(self);
        }
        try {
          String cmdres = doCmd("web", cmd);
          if (TS.isEmpty(cmdres)) {
            "cmdres empty".print();
          } else {
            ("cmdres " + cmdres).print();
            request.outputContent = cmdres;
            return(self);
          }
        } catch (any dce) {
          "except in doCmd".print();
          dce.print();
          request.outputContent = "error handling command";
          return(self);
        }
      } else {
        "sending page".print();
        request.outputContents = webPageL;
        "done sending".print();
      }
   }
   
}
