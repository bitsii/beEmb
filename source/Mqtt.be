// Copyright 2021 The Bennt Embed Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;
use Embedded:MqMessage;

/*
//for Mqtt.be
//in BEAR_Imports.hpp
#include <MQTT.h>
*/

class Embedded:Mqtt {

emit(cc_classHead) {
"""
std::unique_ptr<MQTTClient> client;
WiFiClient net;
static std::string gotTopic;
static std::string gotPayload;
"""
}

emit(cc) {
 """
std::string BEC_2_8_4_EmbeddedMqtt::gotTopic;
std::string BEC_2_8_4_EmbeddedMqtt::gotPayload;

void messageReceived(String &topic, String &payload) {
  //Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.

  //std::string lips = std::string(lip.c_str());
  BEC_2_8_4_EmbeddedMqtt::gotTopic = std::string(topic.c_str());
  BEC_2_8_4_EmbeddedMqtt::gotPayload = std::string(payload.c_str());
}
 """
}

  new() self {
    fields {
      String mqttServer;
      String user;
      String pass;
      Int mqttPort = 1883;
      String id = System:Random.getString(16);
      Container:List mqsubl = Container:List.new();
      Container:List:Iterator mqsubi;
      Embedded:MqttMessage mqpubm;
      Container:List mqpubl = Container:List.new();
      Container:List:Iterator mqpubi;
      Int mqpublmax = 8;
      Embedded:MqttMessage mqrcm;
      Container:List mqrcl = Container:List.new();
      Container:List:Iterator mqrci;
      Int mqrcmax = 8;
      Int zero = 0;
    }
    emit(cc) {
      """
      client = std::make_unique<MQTTClient>(384);
      """
    }
  }

  new(String _mqttServer, String _user, String _pass) self {
    mqttServer = _mqttServer;
    user = _user;
    pass = _pass;
    new();
  }

  minAsyncCapacitySet(Int size) {
    if (mqpublmax < size) {
      mqpublmax.setValue(size);
    }
  }

  hasAsyncCapacity(Int amount) Bool {
    if (mqpublmax >= mqpubl.size && mqpublmax - mqpubl.size >= amount) {
      return(true);
    }
    return(false);
  }

  publishAsync(String pt, String cf) Bool {
    return(publishAsync(Embedded:MqttMessage.new(pt, cf)));
  }

  publishAsync(Embedded:MqttMessage msg) Bool {
    if (hasAsyncCapacity(1)) {
      mqpubl += msg;
      return(true);
    }
    return(false);
  }

  subscribeAsync(String topic) Bool {
    mqsubl += topic;
    return(true);
  }

  isOpenGet() Bool {
    Bool ret;
    emit(cc) {
      """
      if (client->connected()) {
        beq->bevl_ret = BECS_Runtime::boolTrue;
      } else {
        beq->bevl_ret = BECS_Runtime::boolFalse;
      }
        """
      }
    return(ret);
  }

  close() Bool {
    Bool ret;
    emit(cc) {
      """
      if (client->connected()) {
        if (client->disconnect()) {
          beq->bevl_ret = BECS_Runtime::boolTrue;
        } else {
          beq->bevl_ret = BECS_Runtime::boolFalse;
        }
      } else {
        beq->bevl_ret = BECS_Runtime::boolFalse;
      }
      """
    }
    if (ret) {
     "mqtt close succeeded".print();
    } else {
      "mqtt close failed".print();
    }
    return(ret);
  }
  
  open() Bool {
    Bool ret;
    emit(cc) {
      """
      client->begin(bevp_mqttServer->bems_toCcString().c_str(), bevp_mqttPort->bevi_int, net);
      client->onMessage(messageReceived);
      if (client->connect(bevp_id->bems_toCcString().c_str(), bevp_user->bems_toCcString().c_str(), bevp_pass->bems_toCcString().c_str())) {
          beq->bevl_ret = BECS_Runtime::boolTrue;
        } else {
          beq->bevl_ret = BECS_Runtime::boolFalse;
        }
      """
    }
    if (ret) {
     "mqtt opened".print();
    } else {
      "mqtt open failed".print();
    }
    return(ret);
  }

  publish(String topic, String payload) Bool {
    Bool ret;
    //("publishing " + topic + " " + payload).print();
    emit(cc) {
      """
      if (client->publish(beq->beva_topic->bems_toCcString().c_str(), beq->beva_payload->bems_toCcString().c_str())) {
          beq->bevl_ret = BECS_Runtime::boolTrue;
        } else {
          beq->bevl_ret = BECS_Runtime::boolFalse;
        }
      """
    }
    /*if (ret) {
     "mqtt published".print();
    } else {
      "mqtt publish failed".print();
    }*/
    return(ret);
  }

  publish(Embedded:MqttMessage msg) Bool {
    return(publish(msg.topic, msg.payload));
  }

  handleAsync(any mqttHandler) Bool {
    //return is "did I do work"
    String gott;
    String gotp;
    emit(cc) {
      """
      if (!client->loop()) {
        //Serial.println(client->lastError());
        //if got something during recieve, return
      """
    }
    return(false);
    emit(cc) {
      """
    } else {
      if (BEC_2_8_4_EmbeddedMqtt::gotTopic.size() > 0 &&  BEC_2_8_4_EmbeddedMqtt::gotPayload.size() > 0) {
        beq->bevl_gott = new BEC_2_4_6_TextString(BEC_2_8_4_EmbeddedMqtt::gotTopic);
        beq->bevl_gotp = new BEC_2_4_6_TextString(BEC_2_8_4_EmbeddedMqtt::gotPayload);
        BEC_2_8_4_EmbeddedMqtt::gotTopic.clear();
        BEC_2_8_4_EmbeddedMqtt::gotPayload.clear();
      }
    }
      """
    }

    if (TS.notEmpty(gott) && TS.notEmpty(gotp)) {
      if (mqrcmax > mqrcl.size) {
        mqrcl += Embedded:MqttMessage.new(gott, gotp);
      } else {
        "mqrcl full".print();
      }
      return(false);
    }

    if (def(mqsubi)) {
      if (mqsubi.hasNext) {
        String tosub = mqsubi.next;
        subscribe(tosub);
        return(true);
      } else {
        mqsubi = null;
        mqsubl.clear();
        return(false);
      }
    } elseIf (mqsubl.size > zero) {
      mqsubi = mqsubl.iterator;
      return(false);
    }

    if (def(mqrcm)) {
      auto m = mqrcm;
      mqrcm = null;
      mqttHandler.handleMqtt(m.topic, m.payload);
      return(true);
    } elseIf (def(mqrci)) {
      if (mqrci.hasNext) {
        mqrcm = mqrci.next;
        return(false);
      } else {
        mqrci = null;
        return(false);
      }
    } elseIf (mqrcl.size > zero) {
      mqrci = mqrcl.iterator;
      mqrcl = Container:List.new();
      return(false);
    }

    if (def(mqpubm)) {
      //if (publish(mqpubm)) { }
      publish(mqpubm);
      mqpubm = null;
      return(true);
    } elseIf (def(mqpubi)) {
      if (mqpubi.hasNext) {
        mqpubm = mqpubi.next;
        return(false);
      } else {
        mqpubi = null;
        mqpubl.clear();
        return(false);
      }
    } elseIf (mqpubl.size > zero) {
      mqpubi = mqpubl.iterator;
      return(false);
    }

    return(false);
  }

  subscribe(String topic) {
    if (TS.notEmpty(topic)) {
      emit(cc) {
        """
        client->subscribe(beq->beva_topic->bems_toCcString().c_str());
        """
      }
    }
  }
  
}

class Embedded:MqttMessage {
  new(String _topic, String _payload) {
    fields {
      String topic = _topic;
      String payload = _payload;
    }
  }

  toString() String {
    String ret = String.new();
    if (TS.notEmpty(topic)) {
      ret += "Topic:" += topic += ";";
    } else {
      ret += "TopicEmpty:;";
    }
    if (TS.notEmpty(payload)) {
      ret += "Payload:" += payload += ";";
    } else {
      ret += "PayloadEmpty:;";
    }
    return(ret);
  }
}
