/*
 * Copyright (c) 2021-2023, the Brace Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Text:Strings as TS;
use System:Exception;

use Embedded:CommonNames as CNS;

use Embedded:Wifi;

class Embedded:Dfis {

  new(_ash) self {
    slots {
      Embedded:AppShell ash = _ash;
      Int nextOutset = 0;
      Int nextWifiDis = 0;
      List ocmdl;
      String slashn = "\n";
      String slashr = "\r";
      String readBuf = String.new();
      String status;
    }
  }

  start() {

  }

  handleLoop() {
    doDfis();
  }

  doDfis() {
    if (nextWifiDis > 0 && ash.nowup > nextWifiDis) {
      nextWifiDis = 0;
      if (TS.notEmpty(status)) {
        unless (status.begins("success") || status.begins("failed")) {
          status = "failed:Timed out during device setup";
        }
      }
      Wifi.stop();
    }
    if (nextOutset > 0 && ash.nowup > nextOutset) {
      "will outset".print();
      nextOutset = 0;
      status = "start";
      //03:54:27.565 -> ap6 INLVLZXEERMEABMD c0e01d7bd50eb13193f55ab7849195df794064ac 1758365668 OENRHJTDMFXZ dfis X outset CasnicO-cxqlqfwk-NodeMcu-6 cxqlqfwkcxqlqfwk EBWVLFTYMLRHKVZECD CVMYFLSLFOVOBUBYRT MEIACOYEGZTEPHHL e
      if (def(ocmdl) && ocmdl.length > 7) {
        "ocmdl length".print();
        //ocmdl.length.print();//9
        //ocmdl[0].print();dfis
        //ocmdl[1].print();password
        //2 is outset, ...
        ash.nextWifiCheck = ash.nowup + 45000;//45 sec, you get 30s to connect max, 10s for setting, stop 5s wifi
        nextWifiDis = ash.nowup + 40000;//when we give up
        status = "wifi";
        Wifi.new(ocmdl[3], null).start();//in future check for CasnicO vs whatever and do the right thing
        String scmds = "allset";//cmds = "allset " + devPin + " " + devPass + " " + devSpass + " " + devDid + " e";
        for (Int i = 4; i < ocmdl.length;i++) {
           scmds += " " += ocmdl[i];
        }
        String res = sendCmd("192.168.4.1", scmds);
        if (TS.notEmpty(res)) {
          ("allset res " + res).print();
          if (res.has("Error")) {
            status = "failed:" + res;
            ash.nextWifiCheck = ash.nowup + 3000;//we're done here
            nextWifiDis = ash.nowup + 2000;//we're done here
          } else {
            status = "setwifi";
            "sending wifi".print();
            scmds = "setwifi " + ocmdl[5] + " hex " + Encode:Hex.encode(ash.ssid) + " " + Encode:Hex.encode(ash.sec) + " e";
            res = sendCmd("192.168.4.1", scmds);
            if (TS.notEmpty(res)) {
              ("wifi res " + res).print();
              if (res.has("Wifi Setup Written")) {
                "wifi ok restarting".print();
                status = "restart";
                scmds = "restart " + ocmdl[5] + " e";
                res = sendCmd("192.168.4.1", scmds);
                if (TS.notEmpty(res)) {
                  if (res.has("Will restart")) {
                    status = "success";
                  } else {
                    status = "failed:" + res;
                  }
                }
                ash.nextWifiCheck = ash.nowup + 3000;//we're done here
                nextWifiDis = ash.nowup + 2000;//we're done here
              } else {
                status = "failed:" + res;
                ash.nextWifiCheck = ash.nowup + 3000;//we're done here
                nextWifiDis = ash.nowup + 2000;//we're done here
              }
            }
          }
        } else {
          ("res empty").print();
        }
      } else {
        "ocmdl too short or undef".print();
      }
      ocmdl = null;
    }
  }

  handleCmdl(List cmdl) String {
    if (cmdl.length > 2 && cmdl[2] == "outset") {
      "dfis cmdl outset".print();
      ocmdl = cmdl;
      nextOutset = ash.nowup + 3000;
      status = "wait";
      return("dfisotry");
    }
    if (cmdl.length > 2 && cmdl[2] == "status") {
      "dfis cmdl status".print();
      if (TS.notEmpty(status)) {
        return(status);
      }
      return("dfisnostat");
    }
    return("dfisnotok");
  }

  sendCmd(String rip, String scmds) String {
      String mcmdres;
      if (TS.notEmpty(rip) && TS.notEmpty(scmds)) {
        ("rip " + rip).print();
        //look for r and n, send back r n (it's already there) FALSE NOT FROM MQ IT ISN'T
        //String ppay = preq.checkGetPayload(readBuf, slashn);
        var tcpc = Embedded:TCPClient.new(rip, 6420);
        //"open".print();
        tcpc.open();
        //"write".print();
        if (tcpc.connected) {
          tcpc.write(scmds);
          tcpc.write(slashr);
          tcpc.write(slashn);
          //"get tcpcres".print();
          String tcpcres = tcpc.checkGetPayload(readBuf, slashn);
          //"got res".print();
        }
        if (TS.isEmpty(tcpcres)) {
          //"tcpcres empty".print();
          //in case ip changed rewantit
          //mmep.rip = null;
        } else {
          //("tcpcres " + tcpcres).print();
          mcmdres = tcpcres;
        }
      }
      return(mcmdres);
  }

}
