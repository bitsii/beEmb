// Copyright 2021 The BraceEmb Authors. All rights reserved.
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
"""
}

emit(cc) {
 """

 """
}

  new() self {
    fields {
      String mqttServer;
      String user;
      String pass;
      Int mqttPort = 1883;
      String id = System:Random.getString(16);
      Container:List mqpubl = Container:List.new();
      Container:List:Iterator mqpubi;
      Int mqpublmax = 8;
      Int zero = 0;
    }
    emit(cc) {
      """
      client = std::make_unique<MQTTClient>();
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
    if (mqpublmax > mqpubl.size && mqpublmax - mqpubl.size >= amount) {
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

  isOpenGet() Bool {
    Bool t = true;
    Bool f = false
    Bool ret;
    emit(cc) {
      """
      if (client->connected()) {
        beq->bevl_ret = beq->bevl_t;
      } else {
        beq->bevl_ret = beq->bevl_f;
      }
        """
      }
    return(ret);
  }

  close() Bool {
    Bool t = true;
    Bool f = false
    Bool ret;
    emit(cc) {
      """
      if (client->connected()) {
        if (client->disconnect()) {
          beq->bevl_ret = beq->bevl_t;
        } else {
          beq->bevl_ret = beq->bevl_f;
        }
      } else {
        beq->bevl_ret = beq->bevl_f;
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
    Bool t = true;
    Bool f = false
    Bool ret;
    emit(cc) {
      """
      client->begin(bevp_mqttServer->bems_toCcString().c_str(), bevp_mqttPort->bevi_int, net);
      if (client->connect(bevp_id->bems_toCcString().c_str(), bevp_user->bems_toCcString().c_str(), bevp_pass->bems_toCcString().c_str())) {
          beq->bevl_ret = beq->bevl_t;
        } else {
          beq->bevl_ret = beq->bevl_f;
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
    Bool t = true;
    Bool f = false
    Bool ret;
    ("publishing " + topic + " " + payload).print();
    emit(cc) {
      """
      if (client->publish(beq->beva_topic->bems_toCcString().c_str(), beq->beva_payload->bems_toCcString().c_str())) {
          beq->bevl_ret = beq->bevl_t;
        } else {
          beq->bevl_ret = beq->bevl_f;
        }
      """
    }
    if (ret) {
     "mqtt published".print();
    } else {
      "mqtt publish failed".print();
    }
    return(ret);
  }

  publish(Embedded:MqttMessage msg) Bool {
    return(publish(msg.topic, msg.payload));
  }

  handleAsync() Bool {
    //return is "did I do work"
    emit(cc) {
      """
      client->loop();
      """
    }
    if (def(mqpubi)) {
      if (mqpubi.hasNext) {
        Embedded:MqttMessage pmsg = mqpubi.next;
        publish(pmsg);
        return(true);
      } else {
        mqpubi = null;
        mqpubl.clear();
        return(false);
      }
    } elseIf (mqpubl.size > zero) {
      mqpubi = mqpubl.iterator;
    }
    return(false);
  }

  receive() Embedded:MqttMessage {
    return(null);
  }

  subscribe(String topic) {
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
