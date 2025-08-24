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
        clientSec.setInsecure();
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
    ifEmit(smcGm) {
      fields {
        List nrips = List.new(12);
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
        mqclient->setId(bevp_id->bems_toCcString().c_str());
        mqclient->setUsernamePassword(bevp_user->bems_toCcString().c_str(), bevp_pass->bems_toCcString().c_str());
        if (!mqclient->connect(bevp_mqttServer->bems_toCcString().c_str(), bevp_mqttPort->bevi_int)) {
          bevp_connectRes->bevi_int = mqclient->connectError();
        } else {
          bevp_connectRes->bevi_int = 0;
        }
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
        beq->bevl_subRes->bevi_int = mqclient->subscribe(beq->beva_toq->bems_toCcString().c_str());
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
      beq->bevl_cgres->bevi_int = mqclient->connected();
      """
    }
    //("cgres " + cgres).print();
    return(cgres);
  }

  checkGetPayload(String topic, String payload) String {
    payload.clear();
    emit(cc) {
    """
    unsigned long currentTime = millis();
    unsigned long previousTime = 0;
    long timeoutTime = 4000;//was 2000
    if (mqclient->connected()) {
    if (mqclient->parseMessage()) {
    """
    }
    Int chari = Int.new();
    String chars = String.new(1);
    chars.setCodeUnchecked(0, 32);
    chars.length.setValue(1);
    Int zero = 0;
    String tmptop;
    if (def(topic)) {
      topic.clear();
    }
    emit(cc) {
    """
      String lip = mqclient->messageTopic();
      //Serial.println(lip);
      std::string lips = std::string(lip.c_str());
      beq->bevl_tmptop = new BEC_2_4_6_TextString(lips);
      currentTime = millis();
      previousTime = currentTime;
      while (mqclient->connected() && currentTime - previousTime <= timeoutTime) {
        //previousTime = currentTime;  //abs timeoutTime from start of checkGet, or must be under available()
        currentTime = millis();
        if (mqclient->available()) {
          char c = mqclient->read();
          //Serial.write(c);
          beq->bevl_chari->bevi_int = c;
          """
          }
          //("got int " + chari).print();
          //? check for -1 and 255 here too?
          chars.setCodeUnchecked(zero, chari);
          //("got char").print();
          //chars.print();
          payload += chars;
emit(cc) {
"""
        } else {
          //Serial.println("not available");
          """
          }
          if (def(topic) && TS.notEmpty(tmptop)) {
            //"adding tmptop".print();
            topic += tmptop;
          }
          return(payload);
          emit(cc) {
            """
        }
      }
    } else {
      //Serial.println("parseMessage 0");
    }
    } else {
      //Serial.println("no client");
    }
    """
    }
    return(payload);
  }

  publish(String topic, String payload) {
    if (TS.isEmpty(topic) || TS.isEmpty(payload)) {
      "can't publish, missing topic or payload".print();
    }
    //("publishing |" + payload + "| to |" + topic + "|").print();
    emit(cc) {
     """
     if (mqclient->connected()) {
      mqclient->beginMessage(beq->beva_topic->bems_toCcString().c_str());
      mqclient->print(beq->beva_payload->bems_toCcString().c_str());
      //mqclient->print("");
      mqclient->endMessage();
     }
     """
    }
  }

}
