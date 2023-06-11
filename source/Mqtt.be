// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;
use Embedded:MqMessage;

/*
In BEAR_Imports.hpp

//for MQTT.be
#include <PubSubClient.h>

*/

class Embedded:MqttMessage {
  new(String _topic, String _payload) {
    fields {
      String topic = _topic;
      String payload = _payload;
    }
  }
  toString() String {
    String res = String.new();
    if (TS.isEmpty(topic)) {
      res += "EmptyTopic::";
    } else {
      res += "Topic:" + topic + ":";
    }
    if (TS.isEmpty(payload)) {
      res += "EmptyPayload::";
    } else {
      res += "Payload:" + payload + ":";
    }
    return(res);
  }
}

class Embedded:Mqtt {

emit(cc_classHead) {
"""

WiFiClient bevs_wifiClient;
PubSubClient bevs_mqClient;
char bevs_clientId[16];
char bevs_mqUser[16];
char bevs_mqPass[16];
static std::string lastTopic;
static std::string lastMessage;

"""
}

emit(cc) {
 """

 std::string BEC_2_8_4_EmbeddedMqtt::lastTopic;
 std::string BEC_2_8_4_EmbeddedMqtt::lastMessage;

 void mqcallback(char* topic, byte* payload, unsigned int length) {
   //Serial.println("in callback");
   if (length > 0 && topic[0] != '\0') {
      BEC_2_8_4_EmbeddedMqtt::lastTopic.clear();
      BEC_2_8_4_EmbeddedMqtt::lastMessage.clear();
      BEC_2_8_4_EmbeddedMqtt::lastTopic = topic;
      for (int i = 0; i < length; i++) {
        BEC_2_8_4_EmbeddedMqtt::lastMessage.push_back((char)payload[i]);
      }
      //Serial.println(BEC_2_8_4_EmbeddedMqtt::lastTopic.c_str());
      //Serial.println(BEC_2_8_4_EmbeddedMqtt::lastMessage.c_str());
   }
}

 """
}

  new() self {
    fields {
      String mqttServer = "192.168.1.124";
      Int mqttPort = 1883;
      String clientId;
      String user = "";
      String pass = "";
      List messages = List.new();
      Int zero = 0;
    }
    emit(cc) {
      """
     bevs_mqClient.setClient(bevs_wifiClient);
      """
    }
  }

  new(String _mqttServer, String _user, String _pass) self {
    mqttServer = _mqttServer;
    user = _user;
    pass = _pass;
    new();
  }

  connectedGet() Bool {
    emit(cc) {
      """
      if (bevs_mqClient.connected()) {
      """
    }
    return(true);
    emit(cc) {
      """
    }
    """
    }
    return(false);
  }
  
  connect() self {
    if (TS.notEmpty(mqttServer)) {
      if (undef(mqttPort)) {
        mqttPort = 1883;
      }
      if (TS.isEmpty(clientId)) {
        clientId = System:Random.getString(12).lower();
      }
      if (TS.notEmpty(user) && TS.notEmpty(pass)) {
        //("gonna connect |" + user + "| |" + pass + "|").print();
emit(cc) {
  """
  bevs_mqClient.setServer(bevp_mqttServer->bems_toCcString().c_str(), bevp_mqttPort->bevi_int);
  bevp_clientId->bems_c_str(bevs_clientId, 14);
  bevp_user->bems_c_str(bevs_mqUser, 14);
  bevp_pass->bems_c_str(bevs_mqPass, 14);
  if(bevs_mqClient.connect(bevs_clientId, bevs_mqUser, bevs_mqPass)) {
  """
}
       "connected".print();
       subscribe("/test");
       emit(cc) {
         """
         bevs_mqClient.setCallback(mqcallback);
       } else {
         """
       }
       "mqtt connect failed".print();
       emit(cc) {
         """
         Serial.print("failed, rc=");
         Serial.print(bevs_mqClient.state());
       }
         """
       }
      }
    }
    return(self);
  }

  //receive

  publish() Bool {
    publish("/test", "yo pubsub", false);
    return(publish("/test", "yar pubsub", false));
  }

  publish(String topic, String payload) Bool {
    return(publish(topic, payload, false));
  }
  
  publish(String topic, String payload, Bool retained) Bool {
    //"gonna publish".print();
     emit(cc) {
       """
       if(bevs_mqClient.publish(beq->beva_topic->bems_toCcString().c_str(), beq->beva_payload->bems_toCcString().c_str(), beq->beva_retained->bevi_bool)) {
       """
     }
     //"published".print();
     return(true);
     emit(cc) {
       """
     }
       """
     }
     "mqtt publish failed".print();
     return(false);
  }

  process() {
    String lastTopic;
    String lastMessage;
    emit(cc) {
      """
      bevs_mqClient.loop();
      if (!lastTopic.empty()) {
        beq->bevl_lastTopic = new BEC_2_4_6_TextString(lastTopic);
        beq->bevl_lastMessage = new BEC_2_4_6_TextString(lastMessage);
        lastTopic.clear();
        lastMessage.clear();
      }
      """
    }
    if (TS.notEmpty(lastTopic)) {
      //"got something in mqtt process".print();
      //lastTopic.print();
      //lastMessage.print();
      messages += Embedded:MqttMessage.new(lastTopic, lastMessage);
    }
  }

  subscribe(String topic) {
    emit(cc) {
      """
      bevs_mqClient.subscribe(beq->beva_topic->bems_toCcString().c_str());
      """
    }
  }

  receive() List {
    if (messages.length == zero) {
      return(null);
    }
    List toRet = messages.copy();
    messages.clear();
    return(toRet);
  }
  
}
