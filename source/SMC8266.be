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

  //despite the below, only works for esp32 at present
emit(cc_classHead) {
"""

"""
}

  new() self {
    slots {
      String mqttServer;
      String user;
      String pass;
      Bool ssl;
      Int mqttPort;
    }
    fields {
      String fixedId;
      String id;
      Int connectRes = 200;
    }
    if (undef(ssl)) {
      ssl = false;
    }
    if (ssl) {
      emit(cc) {
        """
        """
      }
    } else {
      emit(cc) {
        """
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

  connect() Int {
    if (TS.isEmpty(mqttServer) || undef(mqttPort) || undef(ssl) || TS.isEmpty(user) || TS.isEmpty(pass)) {
      "Unable to connect mqtt, some configuration is missing".print();
      connectRes.setValue(100);
    } else {
      if (TS.notEmpty(fixedId)) {
        id = fixedId;
      } else {
        id = System:Random.getString(16);
      }
      emit(cc) {
        """
        """
      }
    }
    ("mq connect result code " + connectRes).print();
    return(connectRes);
  }

  subscribe(String toq) Int {
   Int subRes = 0;
   if (TS.isEmpty(toq)) {
      "Unable to subscribe bad toq".print();
      subRes.setValue(100);
   } else {
     ("subscribing to " + toq).print();
      emit(cc) {
        """
        """
      }
   }
   ("mq subscribe result code " + subRes).print();
   return(subRes);
  }

  connectedGet() Int {
    Int cgres = 0;
    emit(cc) {
      """
      """
    }
    //("cgres " + cgres).print();
    return(cgres);
  }

  checkGetPayload(String payload) String {
    payload.clear();
    return(payload);
  }

  publish(String topic, String payload) {
    if (TS.isEmpty(topic) || TS.isEmpty(payload)) {
      "can't publish, missing topic or payload".print();
    }
    //("publishing |" + payload + "| to |" + topic + "|").print();
  }

}
