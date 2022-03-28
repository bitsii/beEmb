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
       auto delay = 2; //ms
       String ssidf = "/lawifissid.txt";
       String secf = "/lawifisec.txt";
       String passf = "/ladevpass.txt";
       Int swpin = 2;
       Int tick = 0;
       Files files = Files.new();
       auto upcheckFrequency = 1800; //15 mins at 500ms
       //auto upcheckFrequency = 600;
       auto upcheckCount = 0;
       List webPageL;
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
          ''';
     String htmlBody = '''
     <body>
     <form id="dpformid" action="/" method="get" onsubmit="ajaxSubmit('dpformid');return false;"><input type="hidden" name="dpform" id="dpform" value="dpform"/><label for="fname">Oldpass:</label><input type="text" id="oldpass" name="oldpass"><br>
     <br><label for="lname">Newpass:</label><input type="text" id="newpass" name="newpass"><br>
     <br><input type="submit" value="Set Device Password"></form>
     <form id="wififormid" action="/" method="get" onsubmit="ajaxSubmit('wififormid');return false;"><input type="hidden" name="wifiform" id="wifiform" value="wifiform"/><label for="fname">SSID:</label><input type="text" id="ssid" name="ssid"><br>
     <br><label for="lname">Secret:</label><input type="text" id="sec" name="sec"><br>
     <br><label for="lname">Device Password:</label><input type="text" id="wifidpass" name="wifidpass"><br>
     <br><input type="submit" value="Setup Wifi"></form>
     </body>
     ''';
     String htmlEnd = "</html>";
     webPageL = List.new();
     webPageL += htmlStart;
     webPageL += webPageHead;
     webPageL += htmlBody;
     webPageL += htmlEnd;
     "webpage made".print();
   }
   
   startLoop() {
     "in startLoop LedApp".print();
     app.pinModeOutput(swpin);
     checkWifiAp();
     if (def(Wifi.localIP)) {
      ("Local ip " + Wifi.localIP).print();
      "starting ws".print();
      webserver.start();
     }
   }
   
  checkWifiAp() {
     "in checkWifiAp".print();
     unless (Wifi.up && Wifi.mode == "station") {
      "trying startwifi".print();
      startWifi();
      unless (Wifi.up) {
        "starting ap".print();
        Wifi.new("EspAp", "goodstuff").startAp();
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
       //"checking wifi up".print();
       upcheckCount = 0;
       unless (Wifi.isConnected) {
         app.restart();
       }
     }
   }
   
   handleLoop() {
     tick++=;
     if (tick > 10000) {
      tick = 0;
      "reset tick".print();
      }
     //maybeCheckWifiUp();
     webserver.checkHandleWeb();
     app.delay(delay);
   }
   
    handleWeb(request) {
     "in ledapp handleweb".print();
     "getting params".print();
      String wifiform = request.getParameter("wifiform");
      String dpform = request.getParameter("dpform");
      "checking forms".print();
      Bool needsRestart = false;
      if (TS.notEmpty(wifiform) && wifiform == "wifiform") {
        "got wifiform".print();
        String ssid = request.getParameter("ssid");
        String sec = request.getParameter("sec");
        String wifidpass = request.getParameter("wifidpass");
        "checking ssid".print();
        if (TS.isEmpty(wifidpass)) {
          request.outputContent = "Device Password Required";
          return(self);
        }
        if (files.exists(passf)) {
         pass = files.read(passf);
         if (TS.isEmpty(pass)) {
           request.outputContent = "Device Password Must Be Set";
           return(self);
           }
           if (wifidpass != pass) {
             request.outputContent = "Device Password Incorrect";
             return(self);
           }
         } else {
           request.outputContent = "Device Password Must Be Set";
           return(self);
         }
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
          request.outputContent = "Wifi Setup";
        } else {
          ("ssid missing").print();
          files.delete(ssidf);
          files.delete(secf);
          request.outputContent = "Wifi Setup cleared";
        }
        needsRestart = true;
      } elseIf (TS.notEmpty(dpform) && dpform == "dpform") {
        "got dpform".print();
        String oldpass = request.getParameter("oldpass");
        String newpass = request.getParameter("newpass");
        if (files.exists(passf)) {
         String pass = files.read(passf);
         if (TS.notEmpty(pass)) {
           ("currpass " + pass).print();
           if (TS.isEmpty(oldpass)) {
             request.outputContent = "Error, password is set but oldpass was not sent";
             return(self);
           } elseIf (pass != oldpass) {
             request.outputContent = "Error, oldpass is incorrect";
             return(self);
           }
         }
        }
        if (TS.isEmpty(newpass)) {
         files.delete(passf);
         request.outputContent = "Password cleared";
        } else {
         files.write(passf, newpass);
         request.outputContent = "Password set";
        }
      } else {
        "sending".print();
        request.outputContents = webPageL;
        "done sending".print();
      }
      if (needsRestart) {
        "restarting for new settings".print();
          Wifi.stop();
          Wifi.clearAll();
          app.restart();
        }
   }
   
}
