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
      String amc = "am3:";
      String wac = "want3:";
      String mySay = amc + _myName + "#" + Wifi.localIP;
      String myWants = wac + _myName;
      //String myName = _myName;
      Embedded:AppShell ash = _ash;
      String waits;
      String waitsRip;
      String gots;
      String gotsRip;
      String sayMy;
      String sayWants;
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
    delay(10);
  }
  """
  }
    if (def(msg)) {
      ("be msg|" + msg + "|").print();
      if (msg.begins(amc)) {
        Int ax = msg.find(":");
        Int dx = msg.find("#");
        if (def(dx)) {
          rip = msg.substring(dx + 1, msg.length);
          msg = msg.substring(ax + 1, dx);
        }
        if (TS.notEmpty(rip)) {
          ("be rip|" + rip + "|").print();
          if (TS.notEmpty(waits) && msg == waits) {
            waitsRip = rip;
            if (def(cb)) {
              cb.gotWants(waits, rip);
              cb = null;
            }
          } else {
            gots = msg;
            gotsRip = rip;
          }
        }
      } elseIf (msg == myWants) {
        sayMy = mySay;
      }
    } elseIf (TS.notEmpty(sayMy)) {
      say(sayMy);
      sayMy = null;
    } elseIf (TS.notEmpty(sayWants)) {
      say(sayWants);
      sayWants = null;
    }
  }

  sayWants(String wants) {
    sayWants = wac + wants;
  }

  sayWantsCb(String wants, _cb) {
    slots {
      any cb = _cb;
    }
    sayWants(wants);
  }

  getAddr(String name) String {
    if (TS.notEmpty(name)) {
      if (TS.notEmpty(waits) && waits == name && TS.notEmpty(waitsRip)) {
        return(waitsRip);
      } elseIf (TS.notEmpty(gots) && gots == name && TS.notEmpty(gotsRip)) {
        return(gotsRip);
      } else {
        sayWants(name);
      }
    }
    return(CNS.undefined);
  }

  reallyGetAddr(String kdn) String {
    String rip = getAddr(kdn);
    if (rip == CNS.undefined) {
      for (Int i = 0;i < 3;i++) {
        ("no rip " + i).print();
        update();
        ash.app.delay(15);
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
