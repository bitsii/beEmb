// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;
use Embedded:MqMessage;

/*
In BEAR_Imports.hpp

*/

class Embedded:Mqtt {

emit(cc_classHead) {
"""
std::unique_ptr<MqttClient> mqttClient;
WiFiClient wifiClient;
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
    }
  }

  new(String _mqttServer, String _user, String _pass) self {
    mqttServer = _mqttServer;
    user = _user;
    pass = _pass;
    new();
  }

  poll() {
    emit(cc) {
      """
      mqttClient->poll();
      """
    }
  }

  isOpenGet() Bool {
    emit(cc) {
      """
      if (mqttClient) {
        if (mqttClient->connected()) {
      """
    }
    return(true);
    emit(cc) {
      """
    }
      }
      """
    }
    return(false);
  }

  close() {
    emit(cc) {
      """
      if (mqttClient) {
        mqttClient->stop();
      }
      """
    }
  }
  
  open() Bool {
    Bool didOpen = true;
    emit(cc) {
      """
      mqttClient = std::make_unique<MqttClient>(&wifiClient);
      mqttClient->setId(bevp_id->bems_toCcString().c_str());
      mqttClient->setUsernamePassword(bevp_user->bems_toCcString().c_str(), bevp_pass->bems_toCcString().c_str());
      if (!mqttClient->connect(bevp_mqttServer->bems_toCcString().c_str(), bevp_mqttPort->bevi_int)) {
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(mqttClient->connectError());
        """
      }
      didOpen = false;
    emit(cc) {
      """
      } else {
        Serial.println("MQTT connected");
      }
      """
    }
    return(didOpen);
  }

  publish(String topic, String payload) Bool {
    emit(cc) {
      """
      mqttClient->beginMessage(beq->beva_topic->bems_toCcString().c_str());
      mqttClient->print(beq->beva_payload->bems_toCcString().c_str());
      mqttClient->endMessage();
      """
    }
    return(true);
  }

  handleLoop() Bool {
    return(true);
  }

  subscribe(String topic) {
    emit(cc) {
      """
      mqttClient->subscribe(beq->beva_topic->bems_toCcString().c_str());
      """
    }
  }

  receive() Embedded:MqttMessage {
    emit(cc) {
      """
     int messageSize = mqttClient->parseMessage();
    if (messageSize) {
      """
    }
    Int paysize = Int.new();
    emit(cc) {
      """
      beq->bevl_paysize->bevi_int = messageSize;
      """
    }
    String topic;
    String payload = String.new(paysize);
    Int chari = Int.new();
    String chars = String.new(1);
    chars.setCodeUnchecked(0, 32);
    chars.size.setValue(1);
    Int zero = 0;
    emit(cc) {
      """
    // we received a message, print out the topic and contents
    //Serial.print("Received a message with topic '");
    //Serial.print(mqttClient->messageTopic());

    String tpc = mqttClient->messageTopic();
    std::string tpcs = std::string(tpc.c_str());
    beq->bevl_topic = new BEC_2_4_6_TextString(tpcs);

    //Serial.print("', length ");
    //Serial.print(messageSize);
    //Serial.println(" bytes:");

    // use the Stream interface to print the contents
    //TODO timeout for read
    while (mqttClient->available()) {
      //Serial.print((char)mqttClient->read());
      char c = (char)mqttClient->read();
      //Serial.write(c);
      beq->bevl_chari->bevi_int = c;
      """
    }
    chars.setCodeUnchecked(zero, chari);
    payload += chars;
    emit(cc) {
      """
    }
    } else {
      """
    }
    return(null);
    emit(cc) {
      """
    }
      """
    }

    return(Embedded:MqttMessage.new(topic, payload));

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
