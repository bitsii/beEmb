// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;
use Embedded:MqMessage;


class MqMessage {

  new(String _topic, String _payload) {
    fields {
      String topic = _topic;
      String payload = _payload;
    }
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
static std::vector<std::string> bevs_mqTopics;
static std::vector<std::string> bevs_mqPayloads;

"""
}

emit(cc) {
 """

 std::vector<std::string> BEC_2_8_4_EmbeddedMqtt::bevs_mqTopics;
 std::vector<std::string> BEC_2_8_4_EmbeddedMqtt::bevs_mqPayloads;

 void mqcallback(char* topic, byte* payload, unsigned int length) {
   if (length > 0 && topic[0] != '\0' && BEC_2_8_4_EmbeddedMqtt::bevs_mqTopics.size() < 10) {
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
     std::string topicstr = topic;
     std::string payloadstr;
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    payloadstr.push_back((char)payload[i]);
  }
  //Serial.println();
  //Serial.println("got msg");
  BEC_2_8_4_EmbeddedMqtt::bevs_mqTopics.push_back(topicstr);
  BEC_2_8_4_EmbeddedMqtt::bevs_mqPayloads.push_back(payloadstr);
   }
}
 """
}

  new() self {
    fields {
      String mqttServer;
      Int mqttPort;
      String clientId;
      String user;
      String pass;
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
  
  start() self {
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
       //"connected".print();
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
    emit(cc) {
      """
      bevs_mqClient.loop();
      """
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
    emit(cc) {
      """
      if (BEC_2_8_4_EmbeddedMqtt::bevs_mqTopics.empty()) {
      """
    }
    return(null);
    emit(cc) {
      """
    }
      """
    }
    List msgs = List.new();
    String topic;
    String payload;
    MqMessage msg;
    emit(cc) {
      """
      for (int i = 0;i < BEC_2_8_4_EmbeddedMqtt::bevs_mqTopics.size();i++) {
        beq->bevl_topic = new BEC_2_4_6_TextString(BEC_2_8_4_EmbeddedMqtt::bevs_mqTopics[i]);
        beq->bevl_payload = new BEC_2_4_6_TextString(BEC_2_8_4_EmbeddedMqtt::bevs_mqPayloads[i]);
      """
    }
    msg = MqMessage.new(topic, payload);
    msgs += msg;
    emit(cc) {
      """
    }
    BEC_2_8_4_EmbeddedMqtt::bevs_mqTopics.clear();
    BEC_2_8_4_EmbeddedMqtt::bevs_mqPayloads.clear();
    """
    }
    return(msgs);
  }
  
}
