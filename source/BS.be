// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:Config;

class Embedded:BootStrapApp {
   
   main() {
     slots {
       auto app = Embedded:App.new();
       Int shssidi;
       Int shseci;

       Int nextmin = 0;
       String slashn = "\n";
       String slashr = "\r";
       Int nowup = Int.new();
       String readBuf = String.new();
       String supurl;
     }
     app.plugin = self;

     app.uptime(nowup);
     nextmin = nowup + 60000;

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
       Embedded:TCPServer tcpserver;
     }

     app.wdtFeed();
     app.yield();
     app.wdtDisable();
     initRandom();

     checkWifiAp();

     if (def(Wifi.localIP)) {
      ("Local ip " + Wifi.localIP).print();
      if (Wifi.up) {

        tcpserver = Embedded:TCPServer.new(5309);
        tcpserver.start();

      }

     }

   }
   
  checkWifiAp() {
     //"in checkWifiAp".print();
     unless (Wifi.up && Wifi.mode == "station") {
      startWifi();
      unless (Wifi.up) {
        /*if (TS.notEmpty(pin) && pin.size == 16) {
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
        }*/
      }
     }
   }
   
   startWifi() {
     //"in startWifi".print();
     slots {
       String ssid;
       String sec;
     }
     ssid = "ssid";
     sec = "sec";
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
     if (nowup > nextmin) {
      nextmin = nowup + 60000;
      if (def(supurl) && TS.notEmpty(supurl)) {
        String upurl = supurl;
        supurl = null;
        sysupdate(upurl);
      }
      return(self);
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
     return(doCmdl(channel, cmdl));
   }
   
   doCmdl(String channel, List cmdl) String {
     app.maybeGc();
     app.yield();
     if (cmdl.size < 1) {
       return("no cmd specified");
     }
     String cmd = cmdl[0];

     if (cmd == "setwifi") {
        ssid = cmdl[4];
        sec = cmdl[5];
     } elseIf (cmd == "sysupdate") {
        supurl = cmdl[2];
        return("set supurl");
     } else {
       return("unrecognized command");
     }
      return("Something's fishy");
   }
   
}
