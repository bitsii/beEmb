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
WiFiClient wifiClient;
MqttClient* mqttClient;
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
    }
  }

  new(String _mqttServer, String _user, String _pass) self {
    mqttServer = _mqttServer;
    user = _user;
    pass = _pass;
    new();
  }

  close() self {

  }
  
  open() Bool {
    Bool didOpen = true;
    emit(cc) {
      """
      mqttClient = new MqttClient(&wifiClient);
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

  receive() {
    emit(cc) {
      """
     int messageSize = mqttClient->parseMessage();
    if (messageSize) {
    // we received a message, print out the topic and contents
    Serial.print("Received a message with topic '");
    Serial.print(mqttClient->messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // use the Stream interface to print the contents
    while (mqttClient->available()) {
      Serial.print((char)mqttClient->read());
    }
    Serial.println();
    }
      """
    }

  }
  
}
