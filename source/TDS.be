/*
 * Copyright (c) 2021-2023, the Beysant Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Text:Strings as TS;
use System:Exception;

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

  new(String _myName) self {
    fields {
      String mySay = "am:" + _myName;
      List wantedNames = List.new();
      List wantedAddrs = List.new();
      List happenedNames = List.new();
      List happenedAddrs = List.new();
      Int maxWanted = 5;
      Int maxHappened = 5;
    }
  }

  sayMyName() {
    //want and am
    if (TS.notEmpty(mySay)) {
    ("TDS Saying: " + mySay).print();
    emit(cc) {
      """
    // convert string to char array
    //const char* msg = bevp_mySay->bems_toCcString().c_str();

    //String string = "hello world 86 5";
    String string = bevp_mySay->bems_toCcString().c_str();
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
    sayMyName();
  }

  update() self {
    String rip;
    String msg;
  emit(cc) {
  """
  int sz = udp.parsePacket();
  if (sz > 0 && sz < 250) {
    String rip = udp.remoteIP().toString();
    Serial.print("rcv from: ");
    Serial.println(rip);

    Serial.print("rcv haz: ");
    Serial.println(sz);

    char msg[255];
    const uint8_t *msg8 = (const uint8_t *)msg;
    udp.read(msg, sz);
    msg[sz] = '\0';
    Serial.print("rcv got: ");
    Serial.println(msg);

    std::string rips = std::string(rip.c_str());
    beq->bevl_rip = new BEC_2_4_6_TextString(rips);
    std::string msgs = std::string(msg);
    beq->bevl_msg = new BEC_2_4_6_TextString(msgs);
    delay(10);
  }
  """
  }
    if (def(rip) && def(msg)) {
      ("be rip|" + rip + "|").print();
      ("be msg|" + msg + "|").print();
    }
  }

  getAddress(String name) String {
    return(null);
  }

}
