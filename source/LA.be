// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:Files;

class Embedded:LedApp {
   
   main() {
     fields {
       auto app = Embedded:App.new();
       auto webserver = Embedded:WebServer.new(app);
       auto tcpserver = Embedded:TCPServer.new(app, 55443);
       auto delay = 2; //ms
       String ssidf = "/lawifissid.txt";
       String secf = "/lawifisec.txt";
       String domourlf = "/ladomourl.txt";
       String domousrf = "/ladomousr.txt";
       String domosecf = "/ladomosec.txt";
       Files files = Files.new();
       auto upcheckFrequency = 1800; //15 mins at 500ms
       //auto upcheckFrequency = 600;
       auto upcheckCount = 0;
       String webPage;
       Int swpin = 2;
     }
     app.plugin = self;
     "opening files".print();
     files.open();
     
     "making webPage".print();
     webPage = '''
     <html><body>hi</html></body>
     <form action="/" method="get"><input type="hidden" name="wifiform" id="wifiform" value="wifiform"/><label for="fname">SSID:</label><input type="text" id="ssid" name="ssid"><br>
     <br><label for="lname">Secret:</label><input type="text" id="sec" name="sec"><br>
     <br><input type="submit" value="Setup Wifi"></form>
     <form action="/" method="get"><input type="hidden" name="domoset" id="domoset" value="domoset"/><label for="fname">Domoticz Url</label><input type="text" id="domourl" name="domourl"><br>
     <br><label for="lname">Domoticz User B64:</label><input type="text" id="domousr" name="domousr"><br>
     <br><label for="lname">Domoticz Password B64:</label><input type="text" id="domosec" name="domosec"><br>
     <br><input type="submit" value="Setup Domoticz"></form>
     </body></html>
     ''';
   }
   
   startLoop() {
     "in startLoop LedApp".print();
     app.pinModeOutput(swpin);
     app.digitalWriteHigh(swpin);
     checkWifiAp();
     if (def(Wifi.localIP)) {
      ("Local ip " + Wifi.localIP).print();
      "starting ws".print();
      webserver.start();
      tcpserver.start();
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
     //"in la hl".print();
     maybeCheckWifiUp();
     webserver.checkHandleWeb();
     String payload = tcpserver.checkGetPayload();
     if (TS.notEmpty(payload)) {
       doPayload(payload);
     }
     app.delay(delay);
   }
   
   doPayload(String payload) {
     "in doPayload".print();
     if (payload.has("\"set_power\"")) {
        if (payload.has("\"on\"")) {
          "should turn on".print();
          app.digitalWriteLow(swpin);
        } elseIf (payload.has("\"off\"")) {
          "should turn off".print();
          app.digitalWriteHigh(swpin);
        }
     }
   }
   
   //Content-type: text/html\n\n<html><body>Hello there</body></html>
   handleWeb(request) {
     "in ledapp handleweb".print();
     "getting params".print();
      String wifiform = request.getParameter("wifiform");
      String domoset = request.getParameter("domoset");
      "checking wifiform".print();
      Bool needsRestart = false;
      if (TS.notEmpty(wifiform) && wifiform == "wifiform") {
        String ssid = request.getParameter("ssid");
        String sec = request.getParameter("sec");
        "checking ssid".print();
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
        } else {
          ("ssid missing").print();
          files.delete(ssidf);
          files.delete(secf);
        }
        needsRestart = true;
      }
      
      "checking domoset".print();
      if (TS.notEmpty(domoset) && domoset == "domoset") {
        String domourl = request.getParameter("domourl");
        String domousr = request.getParameter("domousr");
        String domosec = request.getParameter("domosec");
        "checking domovars".print();
        if (TS.notEmpty(domourl) && TS.notEmpty(domousr) && TS.notEmpty(domosec)) {
          ("got domourl " + domourl).print();
          ("got domousr " + domousr).print();
          ("got domosec " + domosec).print();
          files.write(domourlf, domourl);
          files.write(domousrf, domousr);
          files.write(domosecf, domosec);
        } else {
          ("domovars missing").print();
          files.delete(domourlf);
          files.delete(domousrf);
          files.delete(domosecf);
        }
      }
    
        "sending".print();
        request.outputContent = webPage;
      "done sending".print();
      if (needsRestart) {
        "restarting for new settings".print();
          Wifi.stop();
          Wifi.clearAll();
          app.restart();
        }
   }
   
}
