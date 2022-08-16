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

class Embedded:AppShell {
   
   main() {
     fields {
       auto app = Embedded:App.new();
       auto tweb = Embedded:TinyWeb.new();
       auto serserver = Embedded:SerServer.new();
       auto mdserver = Embedded:Mdns.new();
       String pinf = "/laspin.txt";
       String passf = "/ladevpass.txt";
       String ssidf = "/lawifissid.txt";
       String secf = "/lawifisec.txt";
       String didf = "/ladidf.txt";
       Int nextmin = 0;
       Int next10sec = 0;
       Int next15min = 0;
       Int nextday = 0;
       String slashn = "\n";
       String slashr = "\r";
       Files files = Files.new();
       String htmlHead;
       //List webPageL;
       Bool needsRestart = false;
       Int nowup = Int.new();
       String did;
       String devType;
       Int majVer;
       Int minVer;
       String readBuf = String.new();
     }
     app.plugin = self;
     
     app.uptime(nowup);
     next10sec = nowup + 10000;
     nextmin = nowup + 60000;
     next15min = nowup + 900000;
     nextday = nowup + 86400000;
     
     //"opening files".print();
     files.open();
     
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

   doState(String state) String {
     return(state);
   }
   
   clearStates() {

   }
   
   saveStates() {
   }

   checkMakeIds() {
      fields {
        String setupType = "r"; //r - repeating pin, can setup from ssid. s - secret pin, need to know it.
      }
      String pin = files.read(pinf);
      if (TS.isEmpty(pin) || pin.size != 16) {
        if (setupType == "r") {
          pin = System:Random.getString(8);
          pin = pin + pin;
        } else {
          pin = System:Random.getString(16);
        }
        files.write(pinf, pin);
      }

      did = files.read(didf);
      if (TS.isEmpty(did)) {
        did = System:Random.getString(16);
        files.write(didf, did);
      }
   }

   makeSwInfo() {
     devType = "shell";
     majVer = 1;
     minVer = 1;
   }
   
   startLoop() {
     //"in startLoop LedApp".print();
     serserver.start();
     makeSwInfo();
     checkMakeIds();
     checkWifiAp();
     if (def(Wifi.localIP)) {
      ("Local ip " + Wifi.localIP).print();
      if (Wifi.up) {
        tweb.start();
      }
     }
     self.swInfo.print();
     loadStates();
     mdserver.name = "ym" + did;
     mdserver.name.print();
     mdserver.start();
     checkUpd();
   }
   
  checkWifiAp() {
     //"in checkWifiAp".print();
     unless (Wifi.up && Wifi.mode == "station") {
      startWifi();
      unless (Wifi.up) {
        if (files.exists(pinf)) {
          String pin = files.read(pinf);
          if (TS.notEmpty(pin) && pin.size == 16) {
            String ssid = pin.substring(0, 8);
            String sec = pin.substring(8, 16);
            ssid = "y" + setupType + ssid;
            //("ssid from pin " + ssid).print();
            //("sec from pin " + sec).print();
            Wifi.new(ssid, sec).startAp();
          }
        }
      }
     }
   }
   
   startWifi() {
     //"in startWifi".print();
     if (files.exists(ssidf)) {
      String ssid = files.read(ssidf);
      //if (TS.notEmpty(ssid)) {
      //  ("ssid " + ssid).print();
      //}
     }
     if (files.exists(secf)) {
      String sec = files.read(secf);
      //if (TS.notEmpty(sec)) {
      //  ("sec " + sec).print();
      //}
     } else {
       sec = "";
     }
     if (TS.notEmpty(ssid)) {
       Wifi.new(ssid, sec).start();
     }
   }
   
   checkWifiUp() {
    //"checking if wifi up".print();
    unless (Wifi.isConnected) {
       "not up restart".print();
       needsRestart = true;
     }
   }

   checkUpd() {
     //"in checkUpd".print();
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
     for (Int j = 0;j < 50;j++=) {
      Embedded:TCPClient client = Embedded:TCPClient.new(updHost, updPort);
      client.open();
      client.write(updOut);
      for (Int i = 0;i < 1000;i++=) {
        updLine = client.checkGetPayload(updLine, slashr);
        if (TS.notEmpty(updLine)) {
          //"updLine".print();
          //updLine.print();
          if (TS.notEmpty(updLine) && updLine.has("CurrentVer")) {
            break;
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
   }
   
   handleLoop() {
     app.uptime(nowup);
     if (nowup > next10sec) {
      next10sec = nowup + 10000;
      saveStates();
     }
     if (nowup > nextmin) {
      nextmin = nowup + 60000;
      self.swInfo.print();
     }
     if (nowup > next15min) {
      next15min = nowup + 900000;
      checkWifiUp();
     }
     if (nowup > nextday) {
      nextday = nowup + 86400000;
      checkUpd();
     }
     if (serserver.available) {
       String serpay = serserver.checkGetPayload(readBuf, slashn);
     }
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
     //get rid of trailing newline
     if (channel == "serial" && cmdl.size > 0) {
       cmdl.put(cmdl.size - 1, cmdl.get(cmdl.size - 1).swap("\n", ""));
     }
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
     /*if (cmds.has("hexed")) {
       Map ncmds = Map.new();
       for (auto kv in cmds) {
         if (def(kv.value)) {
           ncmds.put(kv.key, Hex.decode(kv.value));
         } else {
           ncmds.put(kv.key, null);
         }
       }
       cmds = ncmds;
     }*/
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
      } elseIf (newpin.size != 16) {
        return("Error, pin must be 16 chars in length");
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
     
     //password check
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
         //if command setstate check a statepass too, for limited perms
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
     } elseIf (cmd == "dostate") {
       //"got dostate".print();
        String state = cmds["state"];
        String stateres = doState(state);
        return(stateres);
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
     } elseIf (cmd == "getdid") {
       return(did);
     } elseIf (cmd == "getdevtype") {
       return(devType);
     } elseIf (cmd == "getmajver") {
       return(majVer.toString());
     } elseIf (cmd == "getminver") {
       return(minVer.toString());
     } elseIf (cmd == "setdid") {
        String newdid = cmds["newdid"];
        if (TS.notEmpty(did) && did.size == 16) {
          did = newdid;
          files.write(didf, did);
          return("did now " + did);
        }
        return("need 16 char did");
     } else {
       return("unrecognized command");
     }
      return("Something's fishy");
   }
   
}
