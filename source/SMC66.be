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
ESP8266 section
//for SMC66.be
#include <MQTT.h>
#include <deque>
#include <mutex>
*/

class Embedded:Smc {

emit(cc_classHead) {
"""
std::unique_ptr<MQTTClient> client;
WiFiClient net;
"""
}

emit(cc) {
 """
std::deque<std::string> topDq;
std::deque<std::string> payDq;
//std::mutex tpLk;

void messageReceived(String &topic, String &payload) {
  //Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.

  std::string gotTopic = std::string(topic.c_str());
  std::string gotPayload = std::string(payload.c_str());

  //tpLk.lock();
  try {
    topDq.push_front(gotTopic);
    payDq.push_front(gotPayload);
  } catch (...) {
  //  tpLk.unlock();
  }
  //tpLk.unlock();
}
 """
}

  new() self {
    slots {
      String mqttServer;
      String user;
      String pass;
      Bool ssl;
      Int mqttPort;
      Bool nextLoop = true;
    }
    fields {
      String fixedId;
      String id;
      Int connectRes = 200;
    }
    if (undef(ssl)) {
      ssl = false;
    }
    ifEmit(smcGm) {
      fields {
        List nrips = List.new(12);
      }
    }
    emit(cc) {
      """
      //one or two arguments for buffer sizes, first is read, second write, if only one same value used for both
      //if no value given / the default is 128 each
      //client = std::make_unique<MQTTClient>(384);
      //client = std::make_unique<MQTTClient>();
      client = std::make_unique<MQTTClient>(256, 128);
      """
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
    }
    emit(cc) {
      """
      client->begin(bevp_mqttServer->bems_toCcString().c_str(), bevp_mqttPort->bevi_int, net);
      client->onMessage(messageReceived);
      if (client->connect(bevp_id->bems_toCcString().c_str(), bevp_user->bems_toCcString().c_str(), bevp_pass->bems_toCcString().c_str())) {
          bevp_connectRes->bevi_int = 0;
        } else {
          bevp_connectRes->bevi_int = 2;
        }
      """
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
        if (client->subscribe(beq->beva_toq->bems_toCcString().c_str())) {
          beq->bevl_subRes->bevi_int = 1;
        }
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
      if (client->connected()) {
        //Serial.println("smc client connected");
        beq->bevl_cgres->bevi_int = 1;
      } else {
        //Serial.println("smc client not connected");
      }
      """
    }
    //("cgres " + cgres).print();
    return(cgres);
  }

  checkGetPayload(String topic, String payload) String {
    //every other time do loop or do the checking of the queues
    payload.clear();
    if (def(topic)) {
      topic.clear();
    }
    if (def(sendTop) && def(sendPay)) {
      reallyPublish(sendTop, sendPay);
      sendTop = null;
      sendPay = null;
      return(payload);
    }
    if (nextLoop) {
      nextLoop = false;
      emit(cc) {
        """
        client->loop();
        delay(10);  // <- fixes some issues with WiFi stability
        """
      }
    } else {
      nextLoop = true;

      emit(cc) {
        """
      std::string gotTopic;
      std::string gotPayload;
      //tpLk.lock();
      try {
        if (!topDq.empty() && !payDq.empty()) {
          gotTopic = topDq.back();
          topDq.pop_back();
          gotPayload = payDq.back();
          payDq.pop_back();

          beq->beva_payload->bevi_bytes.insert(beq->beva_payload->bevi_bytes.begin(), gotPayload.begin(), gotPayload.end());
          beq->beva_payload->bevp_length = nullptr;
          beq->beva_payload->bevp_capacity = nullptr;
          beq->beva_payload->bevp_length = new BEC_2_4_3_MathInt(gotPayload.size());
          beq->beva_payload->bevp_capacity = new BEC_2_4_3_MathInt(gotPayload.size());

          if (beq->beva_topic != nullptr) {
            beq->beva_topic->bevi_bytes.insert(beq->beva_topic->bevi_bytes.begin(), gotTopic.begin(), gotTopic.end());
            beq->beva_topic->bevp_length = nullptr;
            beq->beva_topic->bevp_capacity = nullptr;
            beq->beva_topic->bevp_length = new BEC_2_4_3_MathInt(gotTopic.size());
            beq->beva_topic->bevp_capacity = new BEC_2_4_3_MathInt(gotTopic.size());
          }

        }
      } catch (...) {
        //tpLk.unlock();
      }
      //tpLk.unlock();
        """
      }
    }
    return(payload);
  }

  publish(String topic, String payload) {
    if (TS.isEmpty(topic) || TS.isEmpty(payload)) {
      "can't publish, missing topic or payload".print();
    }
    slots {
      String sendTop = topic;
      String sendPay = payload;
    }
  }

  reallyPublish(String topic, String payload) {
    emit(cc) {
      """
      if (client->connected()) {
        client->publish(beq->beva_topic->bems_toCcString().c_str(), beq->beva_payload->bems_toCcString().c_str());
      }
      """
    }
  }

}
