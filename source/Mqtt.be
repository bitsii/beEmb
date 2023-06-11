// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;

/*
Will be needed in BEAR_Imports.cpp

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

*/

class Embedded:Mqtt {

  emit(cc_classHead) {
  """
    WiFiClient client;
    Adafruit_MQTT_Client* mqtt;
    Adafruit_MQTT_Subscribe* tin;
    Adafruit_MQTT_Publish* tout;
  """
  }
  
  connect() self {
    emit(cc) {
    """
    mqtt = new Adafruit_MQTT_Client(&client, "192.168.1.124", 1883, "ha", "hapass");
    int8_t ret;
    tin = new Adafruit_MQTT_Subscribe(mqtt, "/test");
    mqtt->subscribe(tin);//must be before connect!
    if ((ret = mqtt->connect()) != 0) {
       Serial.println("MQTT connect failed");
       Serial.println(mqtt->connectErrorString(ret));
     } else {
      Serial.println("MQTT Connected!");
      tout = new Adafruit_MQTT_Publish(mqtt, "/test");

     }
    """
    }
  }

  checkGetMessage() {
    emit(cc) {
      """
      Adafruit_MQTT_Subscribe *subscription;
      while ((subscription = mqtt->readSubscription(5000))) {

          Serial.println("Got: ");
          Serial.println((char *)subscription->lastread);

      }
      """
    }
  }

  publish() {
    emit(cc) {
     """
     tout->publish("ada hi");
     """
    }
  }

}
