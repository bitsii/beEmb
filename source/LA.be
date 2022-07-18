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
   
   main() {
     fields {
       auto app = Embedded:App.new();
       //auto webserver = Embedded:WebServer.new(app);
       auto tweb = Embedded:TinyWeb.new();
       auto serserver = Embedded:SerServer.new();
       auto mdserver = Embedded:Mdns.new();
       String pinf = "/laspin.txt";
       String passf = "/ladevpass.txt";
       String ssidf = "/lawifissid.txt";
       String secf = "/lawifisec.txt";
       //String udpRes;
       Int nextmin = 0;
       Int next10sec = 0;
       Int next15min = 0;
       String serpayend = "\n";
       Files files = Files.new();
       List webPageL;
       Bool needsRestart = false;
       Int nowup = Int.new();
     }
     app.plugin = self;
     
     app.uptime(nowup);
     next10sec = nowup + 10000;
     nextmin = nowup + 60000;
     next15min = nowup + 900000;
     
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
     webPageL += htmlEnd;
     "webpage made".print();
   }
   
   loadStates() {
     fields {
       String savesas = String.new();
       String lastsavesas = String.new();
       Map states = Map.new();
       Map levels = Map.new();
       String statesf = "/latstates.txt";
     }
     if (files.exists(statesf)) {
       lastsavesas = files.read(statesf, lastsavesas);
       auto cpls = lastsavesas.split(":");
       for (String cpl in cpls) {
         auto kv = cpl.split(",");
         setState("setlevel:" += kv[0] += ":" += kv[1]);
         levels.put(kv[0], kv[2]);
       }
     }
   }
   
   setState(String state) String {
     if (TS.notEmpty(state)) {
      if (state.begins("setlevel")) {
        //"on setlevel".print();
        auto lvls = state.split(":");
        if (lvls.size < 3 || lvls[1].isInteger! || lvls[2].isInteger!) {
          "syntax setlevel:pin:numericlevel (0-255)".print();
          return("invalid");
        }
        Int pini = Int.new(lvls[1]);
        Int lvli = Int.new(lvls[2]);
        //("analog write " + pini + " " + lvli).print();
        app.pinModeOutput(pini);
        app.analogWrite(pini, lvli);
        states[pini] = lvli;
      } elseIf (state.begins("setrlevel")) {
        //"on setlevel".print();
        lvls = state.split(":");
        if (lvls.size < 3 || lvls[1].isInteger! || lvls[2].isInteger!) {
          "syntax setlevel:pin:numericlevel (0-255)".print();
          return("invalid");
        }
        pini = Int.new(lvls[1]);
        lvli = Int.new(lvls[2]);
        lvli = 255 - lvli;
        //("analog write " + pini + " " + lvli).print();
        app.pinModeOutput(pini);
        app.analogWrite(pini, lvli);
        states[pini] = lvli;
       } elseIf (state.begins("delevel")) {
         lvls = state.split(":");
         pini = Int.new(lvls[1]);
         lvli = states[pini];
         if (undef(lvli)) {
           lvli = 255;
         }
         levels.put(pini, lvli);
         lvli = 255;
         app.pinModeOutput(pini);
         app.analogWrite(pini, lvli);
         states[pini] = lvli;
       } elseIf (state.begins("relevel")) {
         lvls = state.split(":");
         pini = Int.new(lvls[1]);
         lvli = levels[pini];
         if (undef(lvli) || lvli == 255) {
           lvli = 0;
         }
         states.put(pini, lvli);
         app.pinModeOutput(pini);
         app.analogWrite(pini, lvli);
       } else {
         state = "invalid";
       }
     } else {
       state = "unset";
     }
     return(state);
   }
   
   clearStates() {
     if (files.exists(statesf)) {
       files.delete(statesf);
     }
     states = Map.new();
     levels = Map.new();
     lastsavesas.clear();
   }
   
   saveStates() {
     savesas.clear();
     for (auto kv in states) {
       if (TS.notEmpty(savesas)) { savesas += ":"; }
       savesas += kv.key += "," += kv.value;
       if (levels.has(kv.key)) {
         savesas += "," += levels.get(kv.key);
       } else {
         savesas += "," += kv.value;
       }
     }
     if (TS.isEmpty(savesas)) {
       return(self);
     }
     if (savesas != lastsavesas) {
       "writing statesf".print();
       files.write(statesf, savesas);
       lastsavesas.clear();
       lastsavesas.copyValue(savesas, 0, savesas.size, 0);
     }
   }
   
   startLoop() {
     "in startLoop LedApp".print();
     serserver.start();
     checkWifiAp();
     if (def(Wifi.localIP)) {
      ("Local ip " + Wifi.localIP).print();
      //"starting ws".print();
      //webserver.start();
      if (Wifi.up) {
        "starting tweb".print();
        tweb.start();
      }
     }
     loadStates();
     mdserver.name = "espyo";
     mdserver.start();
   }
   
  checkWifiAp() {
     "in checkWifiAp".print();
     unless (Wifi.up && Wifi.mode == "station") {
      "trying startwifi".print();
      startWifi();
      unless (Wifi.up) {
        if (files.exists(pinf)) {
          String pin = files.read(pinf);
          if (TS.notEmpty(pin) && pin.size > 19) {
            String ssid = pin.substring(0, 8);
            String sec = pin.substring(8, 16);
            ("ssid from pin " + ssid).print();
            ("sec from pin " + sec).print();
            "starting ap".print();
            Wifi.new(ssid, sec).startAp();
          }
        }
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
   
   checkWifiUp() {
    "checking if wifi up".print();
    unless (Wifi.isConnected) {
       "not up restart".print();
       needsRestart = true;
     }
   }
   
   handleLoop() {
     app.uptime(nowup);
     if (nowup > next10sec) {
      next10sec = nowup + 10000;
      saveStates();
     }
     if (nowup > nextmin) {
      nextmin = nowup + 60000;
      "another minute gone".print();
     }
     if (nowup > next15min) {
      next15min = nowup + 900000;
      checkWifiUp();
     }
     if (serserver.available) {
       auto serpay = serserver.checkGetPayload(String.new(), serpayend);
     }
     if (TS.notEmpty(serpay)) {
       try {
          serpay = serpay.swap("\n", "");
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
                 //("cdec " + cdec).print();
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
     mdserver.update();
     if (needsRestart) {
       needsRestart = false;
       "restarting because needsRestart".print();
        Wifi.stop();
        Wifi.clearAll();
        app.restart();
     }
   }
   
   doCmd(String channel, String cmdline) String {
     if (TS.isEmpty(cmdline)) {
       "cmdline empty".print();
       return("cmdline empty");
     }
     if (TS.isEmpty(channel)) {
       "channel empty".print();
       return("channel empty");
     }
     //check max length and num of spaces
     ("cmdline follows").print();
     cmdline.print();
     ("cmd channel follows").print();
     channel.print();
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
       //"no cmd".print();
       return("no cmd specified");
     }
     //("cmd is " + cmd).print();
     if (cmd == "fullreset") {
      //"got fullreset".print();
      unless (channel == "serial") {
        return("Error, only supported over Serial");
      }
      clearStates();
      files.delete(passf);
      files.delete(ssidf);
      files.delete(secf);
      files.delete(pinf);
      return("All config and pin cleared");
    } elseIf (cmd == "setpin") {
      //"got setpin".print();
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
       clearStates();
       files.delete(passf);
       files.delete(ssidf);
       files.delete(secf);
       files.write(pinf, newpin);
       return("Pin set, configuration cleared");
      }
    } elseIf (cmd == "setpasswithpin") {
      //"got setpasswithpin".print();
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
       clearStates();
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
      clearStates();
      files.delete(passf);
      files.delete(ssidf);
      files.delete(secf);
      return("All config cleared");
     } elseIf (cmd == "setpasswithpass") {
       //"got setpasswithpass".print();
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
       //"got setwifi".print();
        String ssid = cmds["ssid"];
        String sec = cmds["sec"];
        if (TS.notEmpty(ssid)) {
          //("got ssid " + ssid).print();
          files.write(ssidf, ssid);
          if (TS.notEmpty(sec)) {
            //("got sec " + sec).print();
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
       //"got setstate".print();
        String newstate = cmds["newstate"];
        String stateres = setState(newstate);
        return("State now " + stateres);
     } elseIf (cmd == "clearstates") {
       //"got clearStates".print();
        clearStates();
        return("State cleared");
     } elseIf (cmd == "restart") {
       //"got restart".print();
       needsRestart = true;
       return("Will restart soonish");
     } elseIf (cmd == "resetwithpass") {
       clearStates();
       files.delete(passf);
       files.delete(ssidf);
       files.delete(secf);
       return("All config cleared");
     } else {
       return("unrecognized command");
     }
      return("Something's fishy");
   }
   
}
