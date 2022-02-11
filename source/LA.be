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
       String swstatef = "/laswstate.txt";
       String iataddrf = "/laiataddr.txt";
       String iatportf = "/laiatport.txt";
       String iatsecf = "/laiatsec.txt";
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
     <html><body>
     <form action="/" method="get"><input type="hidden" name="wifiform" id="wifiform" value="wifiform"/><label for="fname">SSID:</label><input type="text" id="ssid" name="ssid"><br>
     <br><label for="lname">Secret:</label><input type="text" id="sec" name="sec"><br>
     <br><input type="submit" value="Setup Wifi"></form>
     <form action="/" method="get"><input type="hidden" name="iatset" id="iatset" value="iatset"/><label for="fname">Itsii Addr:</label><input type="text" id="iataddr" name="iataddr"><br>
     <br><label for="lname">Itsii Port:</label><input type="text" id="iatport" name="iatport"><br>
     <br><label for="lname">Itsii Secret:</label><input type="text" id="iatsec" name="iatsec"><br>
     <br><input type="submit" value="Setup Itsii"></form>
     </body></html>
     ''';
     
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
     checkswstate();
     //checkaes();
   }
   
   checkIatLogin() {
     fields {
       Embedded:TCPClient client;
       String deviceid;
       String iv;
       String key;
     }
     if (def(client) && client.connected) {
       //"iat logged in".print();
       return(self);
     }
     //iat addr port sec
     //if have configs and not logged in do it
     //"in checkIatLogin".print();
     if (files.exists(iataddrf)) {
      String addr = files.read(iataddrf);
     }
     if (files.exists(iatportf)) {
      String port = files.read(iatportf);
     }
     if (files.exists(iatsecf)) {
      String token = files.read(iatsecf);
     }
     if (TS.isEmpty(addr) || TS.isEmpty(port) || TS.isEmpty(token)) {
       return(self);
     }
     //("token not empty is " + token).print();
     deviceid = token.substring(0, 16);
     iv = token.substring(16, 32);
     key = token.substring(32, 48);
     client = Embedded:TCPClient.new(addr, Int.new(port));
     client.open();
     client.write(deviceid + "\n");
     Int tries = 20;
     while(client.connected && tries > 0) {
       String payload = client.checkGetPayload("\n");
       if (TS.notEmpty(payload)) {
         ("payload " + payload).print();
         payload = payload.substring(0, payload.size - 1);
         String crn = Hex.decode(payload);
         String nonces = Crypt.decrypt(iv, key, crn);
         ("nonces " + nonces).print();
         Int nonce = Int.new(nonces);
         nonce++=;
         crn = Crypt.encrypt(iv, key, nonce.toString());
         payload = Hex.encode(crn);
         client.write(payload + "\n");
         break;
       }
       tries--=;
       app.delay(50);
     }
     if (client.connected! || tries <= 0) {
       //didn't really login
       //"login failed".print();
       auto cl2 = client;
       client = null;
       cl2.close();
     } else {
       "login succeeded".print();
     }
   }
   
   checkIatState() {
     //if iatlogged in see if we got anything
     //also maybe ping every once in a while
     if (def(client) && client.connected) {
       String payload = client.checkGetPayload("\n");
       if (TS.notEmpty(payload)) {
         ("payload " + payload).print();
         payload = payload.substring(0, payload.size - 1);
         String crn = Hex.decode(payload);
         String payloadin = Crypt.decrypt(iv, key, crn);
         ("payloadin " + payloadin).print();
         doPayload(payloadin);
       }
     }
   }
   
   /*
   checkaes() {
     "trying aes".print();
     String iv = "0123456789012345";
     String key = "0123456789012345";
     String crypted = Embedded:Aes.new().encrypt(iv, key, "turn it on or off maybe yeah");
     String cryptedHex = Encode:Hex.encode(crypted);
     "cryptedHex".print();
     cryptedHex.print();
     String cryptedDeHex = Encode:Hex.decode(cryptedHex);
     String decrypted = Embedded:Aes.new().decrypt(iv, key, cryptedDeHex);
     "decrypted".print();
     decrypted.print();
   }
   */
   
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
     checkIatLogin();
     checkIatState();
     app.delay(delay);
   }
   
   checkswstate() {
     if (files.exists(swstatef)) {
       String payload = files.read(swstatef);
       if (TS.notEmpty(payload)) {
         doPayload(payload);
       }
     } else {
       app.digitalWriteHigh(swpin);
     }
   }
   
   doPayload(String payload) {
     "in doPayload".print();
     if (TS.notEmpty(payload)) {
       ("payload " + payload).print();
     }
     if (payload.has("\"set_power\"")) {
        if (payload.has("\"on\"")) {
          "should turn on".print();
          app.digitalWriteLow(swpin);
          files.write(swstatef, "\"set_power\" \"on\"");
        } elseIf (payload.has("\"off\"")) {
          "should turn off".print();
          app.digitalWriteHigh(swpin);
          files.write(swstatef, "\"set_power\" \"off\"");
        }
     }
   }
   
   //Content-type: text/html\n\n<html><body>Hello there</body></html>
   handleWeb(request) {
     "in ledapp handleweb".print();
     "getting params".print();
      String wifiform = request.getParameter("wifiform");
      String iatset = request.getParameter("iatset");
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
      
      "checking iatset".print();
      if (TS.notEmpty(iatset) && iatset == "iatset") {
        String iataddr = request.getParameter("iataddr");
        String iatport = request.getParameter("iatport");
        String iatsec = request.getParameter("iatsec");
        "checking iatvars".print();
        if (TS.notEmpty(iataddr) && TS.notEmpty(iatport) && TS.notEmpty(iatsec)) {
          ("got iataddr " + iataddr).print();
          ("got iatport " + iatport).print();
          ("got iatsec " + iatsec).print();
          files.write(iataddrf, iataddr);
          files.write(iatportf, iatport);
          files.write(iatsecf, iatsec);
        } else {
          ("iatvars missing").print();
          files.delete(iataddrf);
          files.delete(iatportf);
          files.delete(iatsecf);
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
