// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;

class Embedded:Mqtt {

emit(cc_classHead) {
"""

WiFiClient wifiClient;
PubSubClient mqClient;
char clientId[16];
char user[16];
char pass[16];

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
     mqClient.setClient(wifiClient);
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
  mqClient.setServer(bevp_mqttServer->bems_toCcString().c_str(), bevp_mqttPort->bevi_int);
  bevp_clientId->bems_c_str(clientId, 14);
  bevp_user->bems_c_str(user, 14);
  bevp_pass->bems_c_str(pass, 14);
  if(mqClient.connect(clientId, user, pass)) {
  """
}
       //"connected".print();
       emit(cc) {
         """
       } else {
         """
       }
       "mqtt connect failed".print();
       emit(cc) {
         """
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
       if(mqClient.publish(beq->beva_topic->bems_toCcString().c_str(), beq->beva_payload->bems_toCcString().c_str(), beq->beva_retained->bevi_bool)) {
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
      mqClient.loop();
      """
    }
  }
  
}
