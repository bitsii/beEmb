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
use Encode:Url as EU;

class Embedded:LedApp {
   
   clearState() {
     files.delete(statef);
   }
   
   main() {
     fields {
       auto app = Embedded:App.new();
       //auto webserver = Embedded:WebServer.new(app);
       auto tweb = Embedded:TinyWeb.new();
       auto serserver = Embedded:SerServer.new();
       auto delay = 4; //ms
       String pinf = "/laspin.txt";
       String passf = "/ladevpass.txt";
       String ssidf = "/lawifissid.txt";
       String secf = "/lawifisec.txt";
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
     String htmlHead = String.new();
     htmlHead += "HTTP/1.1 200 OK\r\n";
     htmlHead += "Content-type:text/html\r\n";
     htmlHead += "Connection: close\r\n";
     htmlHead += "\r\n";
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
     webPageL += htmlHead;
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
         "should turn off".print();
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
      //"starting ws".print();
      //webserver.start();
      "starting tweb".print();
      tweb.start();
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
      //"checking wifi and rps".print();
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
     //webserver.checkHandleWeb();
     auto treq = tweb.checkGetRequest();
     if (def(treq)) {
       //"got treq".print();
       String qs = treq.checkGetQueryString();
       if (TS.notEmpty(qs)) {
         if (qs == "/") {
           "base qs sending webpage".print();
           for (String part in webPageL) {
             treq.client.write(part);
           }
         } elseIf (qs.begins("/?")) {
           qs = qs.substring(2, qs.size);
           auto qspso = qs.split("&");
           for (String qspsi in qspso) {
             if (TS.notEmpty(qspsi)) {
               //("got qspsi " + qspsi).print();
               auto qsps = qspsi.split("=");
               if (qsps.size > 1 && def(qsps[0]) && qsps[0] == "cmd" && TS.notEmpty(qsps[1])) {
                 //("got cmd " + qsps[1]).print();
                 String cdec = EU.decode(qsps[1]);
                 ("cdec " + cdec).print();
                 try {
                    cmdres = doCmd("web", cdec);
                    treq.client.write(webPageL[0]); //ok headers
                    if (TS.isEmpty(cmdres)) {
                    //  "cmdres empty".print();
                      treq.client.write("cmdres empty");
                    } else {
                    //  ("cmdres " + cmdres).print();
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
     }
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
     if (cmd == "fullreset") {
     "got reset".print();
      unless (channel == "serial") {
        return("Error, only supported over Serial");
      }
      clearState();
      files.delete(passf);
      files.delete(ssidf);
      files.delete(secf);
      files.delete(pinf);
      return("All config and pin cleared");
    } elseIf (cmd == "setpin") {
     "got setpin".print();
      String newpin = cmds["newpin"];
      unless (channel == "serial") {
        return("Error, only supported over Serial");
      }
      if (TS.isEmpty(newpin)) {
       return("Error, pin is required");
      } elseIf (newpin.isAlphaNum!) {
        return("Error, pin many only consist of letters and numbers");
      } elseIf (newpin.size < 20 || newpin.size > 32) {
        return("Error, pin must be between 20 and 32 chars in length");
      } else {
       clearState();
       files.delete(passf);
       files.delete(ssidf);
       files.delete(secf);
       files.write(pinf, newpin);
       return("Pin set, configuration cleared");
      }
    } elseIf (cmd == "setpasswithpin") {
     "got setpasspin".print();
      String inpin = cmds["pin"];
      String newpass = cmds["newpass"];
      if (files.exists(pinf)) {
       String pin = files.read(pinf);
       if (TS.notEmpty(pin)) {
         if (TS.isEmpty(inpin)) {
           return("Error, pin was not sent");
         } elseIf (pin != inpin) {
           return("Error, pin is incorrect");
         }
       } else {
         return("Error, pin must be set");
       }
      } else {
       return("Error, pin must be set");
      }
      if (TS.isEmpty(newpass)) {
       return("Error, new password is required");
      } else {
       clearState();
       files.delete(ssidf);
       files.delete(secf);
       files.write(passf, newpass);
       return("Password set, other configuration cleared");
      }
     } elseIf (cmd == "resetwithpin") {
      inpin = cmds["pin"];
      if (files.exists(pinf)) {
       pin = files.read(pinf);
       if (TS.notEmpty(pin)) {
         if (TS.isEmpty(inpin)) {
           return("Error, pin was not sent");
         } elseIf (pin != inpin) {
           return("Error, pin is incorrect");
         }
       } else {
         return("Error, pin must be set");
       }
      } else {
       return("Error, pin must be set");
      }
      clearState();
      files.delete(passf);
      files.delete(ssidf);
      files.delete(secf);
      return("All config cleared");
     } elseIf (cmd == "setpasswithpass") {
       "got setpass".print();
        String inpass = cmds["pass"];
        newpass = cmds["newpass"];
        if (files.exists(passf)) {
         String pass = files.read(passf);
         if (TS.notEmpty(pass)) {
           if (TS.isEmpty(inpass)) {
             return("Error, pass was not sent");
           } elseIf (pass != inpass) {
             return("Error, pass is incorrect");
           }
         } else {
           return("Error, password may only be changed if initialized via setpasspin");
         }
        } else {
         return("Error, password may only be changed if initialized via setpasspin");
        }
        if (TS.isEmpty(newpass)) {
         return("Error, new password is required");
        } else {
         files.write(passf, newpass);
         return("Password set");
        }
      }
      
      //if cmd is setstate, check userkey and token, if any good skip pass check
     
     if (files.exists(passf)) {
       inpass = cmds["pass"];
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
          return("Wifi Setup Written, restart to activate");
        } else {
          ("ssid missing").print();
          files.delete(ssidf);
          files.delete(secf);
          return("Wifi Setup cleared, restart to activate");
        }
     } elseIf (cmd == "setstate") {
       "got setstate".print();
        String newstate = cmds["newstate"];
        String stateres = doState(newstate);
        return("State now " + stateres);
     } elseIf (cmd == "restart") {
       "got restart".print();
       needsRestart = true;
       return("Will restart soonish");
     } elseIf (cmd == "resetwithpass") {
       clearState();
       files.delete(passf);
       files.delete(ssidf);
       files.delete(secf);
       return("All config cleared");
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
