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

/*
Will be needed in BEAR_Imports.hpp

ESP32 section
//for TDS
#include <NetworkUdp.h>

ESP8266 section
//for TDS
#include <WiFiUdp.h>

*/

class Embedded:Tds {

  emit(cc_classHead) {
  """

#ifdef BEAR_ESP8266
  WiFiUDP udp;
#endif
#ifdef BEAR_ESP32
  NetworkUDP udp;
#endif

IPAddress broadcast=IPAddress(239, 255, 254, 117);
const int port = 3121;

  """
  }

  new(String _myName, _ash) self {
    slots {
      String amc = "am2:";
      String wac = "want2:";
      String mySay = amc + _myName + "#" + Wifi.localIP;
      String myWants = wac + _myName;
      //w - wanted (requested names)
      //h - happened - some we got, wanted or not
      //N - names
      //A - addrs
      //m - max we'll hold
      //o - spot we're on for new ones
      List wN = List.new();
      List wA = List.new();
      List hN = List.new();
      List hA = List.new();
      Int oW = 0;
      Int oH = 0;
      String myName = _myName;
      Embedded:AppShell ash = _ash;
    }
    fields {
      Int mW = 6;
      Int mH = 3;
      String wants;
    }
  }

  say(String toSay) {
    //want and am
    if (TS.notEmpty(toSay)) {
    ("TDS Saying: " + toSay).print();
    emit(cc) {
      """
    // convert string to char array
    //const char* msg = bevp_mySay->bems_toCcString().c_str();

    //String string = "hello world 86 5";
    String string = beq->beva_toSay->bems_toCcString().c_str();
    // convert string to char array
    char msg[255];
    string.toCharArray(msg,255);

    const uint8_t *msg8 = (const uint8_t *)msg;

    udp.beginPacket(broadcast, port);
    udp.write(msg8, strlen(msg));
    udp.endPacket();
    delay(10);

    """
    }
    }
  }

  startListen() self {
    "TDS starting multicast listen".print();
    emit(cc) {
    """
#ifdef BEAR_ESP8266
  udp.beginMulticast(WiFi.localIP(), broadcast, port);
#endif
#ifdef BEAR_ESP32
  udp.beginMulticast(broadcast, port);
#endif
    """
    }
  }
  
  start() self {
    startListen();
    say(mySay);
  }

  update() self {
    String rip;
    String msg;
  emit(cc) {
  """
  int sz = udp.parsePacket();
  if (sz > 0 && sz < 250) {
    //String rip = udp.remoteIP().toString();
    //Serial.print("rcv from: ");
    //Serial.println(rip);

    //Serial.print("rcv haz: ");
    //Serial.println(sz);

    char msg[255];
    const uint8_t *msg8 = (const uint8_t *)msg;
    udp.read(msg, sz);
    msg[sz] = '\0';
    //Serial.print("rcv got: ");
    //Serial.println(msg);

    //std::string rips = std::string(rip.c_str());
    //beq->bevl_rip = new BEC_2_4_6_TextString(rips);
    std::string msgs = std::string(msg);
    beq->bevl_msg = new BEC_2_4_6_TextString(msgs);
    delay(20);
  }
  """
  }
    if (def(msg)) {
      ("be msg|" + msg + "|").print();
      if (msg.begins(amc)) {
        Int dx = msg.find("#");
        if (def(dx)) {
          rip = msg.substring(dx + 1, msg.length);
          msg = msg.substring(0, dx);
        }
        if (TS.notEmpty(rip)) {
          ("be rip|" + rip + "|").print();
          Int p = wN.find(msg);
          if (def(p)) {
            wA.put(p, rip);
          } else {
            p = hN.find(msg);
            if (def(p)) {
              hA.put(p, rip);
            } else {
              hN.put(oH, msg);
              hA.put(oH, rip);
              oH++;
              if (oH >= mH) {
                oH = 0;
              }
            }
          }
        }
      } elseIf (msg == myWants) {
        say(mySay);
      } elseIf (msg.begins(wac)) {
        String wnm = msg.substring(wac.length, msg.length);
        mdnsGet(wnm);
      }
    } elseIf (TS.notEmpty(wants)) {
      say(wac + wants);
      mdnsGet(wants);
      wants = null;
    }
  }

  mdnsGet(wnm) {
    ifNotEmit(noMdns) {
    if (TS.notEmpty(wnm)) {
      //("in mdnsGet |" + wnm + "|").print();
      if (def(ash.mdserver)) {
        String tqip = ash.mdserver.getAddr(wnm);
        if (TS.notEmpty(tqip)) {
          //("mdnsGet tqip |" + tqip + "|").print();
          say(amc + wnm + "#" + tqip);
        } else {
          //"tqip empty".print();
        }
      }
    } else {
      //"got empty wnm in mdnsGet".print();
    }
    }
  }

  getAddr(String name) String {
    String msg = amc + name;
    String res;
    Int p = wN.find(msg);
    if (def(p)) {
      res = wA.get(p);
    } else {
      p = hN.find(msg);
      if (def(p)) {
       res = hA.get(p);
      } else {
        wN.put(oW, msg);
        wA.put(oW, null);
        oW++;
        if (oW >= mW) {
          oW = 0;
        }
      }
    }
    if (TS.isEmpty(res)) {
      res = CNS.undefined;
      wants = name;
    }
    return(res);
  }

  reallyGetAddr(String kdn) String {
    String rip = getAddr(kdn);
    if (rip == CNS.undefined) {
      for (Int i = 0;i < 5;i++) {
        ("no rip " + i).print();
        update();
        ash.app.delay(25);
        update();
        rip = getAddr(kdn);
        if (rip != CNS.undefined) {
          break;
        }
      }
    }
    return(rip);
  }

}
