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
use Embedded:Smsg;

/*
in BEAR_Imports.hpp

ESP32 section
//for SMC.be
#include <NetworkClientSecure.h>
#include <ArduinoMqttClient.h>

ESP8266 section
//for SMC.be
#include <ArduinoMqttClient.h>
*/

class Embedded:Smc {

emit(cc_classHead) {
"""
#ifdef BEAR_ESP8266
WiFiClient client;
WiFiClientSecure clientSec;
#endif
#ifdef BEAR_ESP32
NetworkClient client;
NetworkClientSecure clientSec;
#endif
std::unique_ptr<MqttClient> mqclient;
"""
}

  new() self {
    fields {
      String mqttServer;
      String user;
      String pass;
      Bool ssl;
      Int mqttPort;
      String id = System:Random.getString(16);
    }
    if (undef(ssl)) {
      ssl = false;
    }
    if (ssl) {
      emit(cc) {
        """
        mqclient = std::make_unique<MqttClient>(clientSec);
        """
      }
    } else {
      emit(cc) {
        """
        mqclient = std::make_unique<MqttClient>(client);
        """
      }
    }
  }

  new(String _mqttServer, Int _mqttPort, Bool _ssl, String _user, String _pass) self {
    mqttServer = _mqttServer;
    mqttPort = _mqttPort;
    ssl = _ssl;
    user = _user;
    pass = _pass;
    new();
  }

}
