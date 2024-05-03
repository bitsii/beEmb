/*
 * Copyright (c) 2021-2023, the Bennt Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Text:Strings as TS;
use System:Exception;

class Embedded:Mdns {

  new(String _name, String _service, Int _port, String _protocol) self {
    slots {
      String name =  _name;
      String service = _service;
      Int port = _port;
      String protocol = _protocol;
    }
  }
  
  start() self {
    if (TS.isEmpty(name)) {
      "mdns needs a name".print();
      return(self);
    }
    emit(cc) {
    """
    int tries = 100;
    if (!MDNS.begin(bevp_name->bems_toCcString().c_str())) {
      Serial.println("Error setting up MDNS responder!");
      while (tries-- > 0) { delay(1000); }
    }
    Serial.println("mDNS responder started");
    """
    }
    if (def(port) && TS.notEmpty(service) && TS.notEmpty(protocol)) {
      emit(cc) {
        """
        MDNS.addService(bevp_service->bems_toCcString().c_str(), bevp_protocol->bems_toCcString().c_str(), bevp_port->bevi_int);
        Serial.println("mDNS service added");
        """
      }
    }
    return(self);
  }
  
  update() self {
  emit(cc) {
  """
  MDNS.update();
  """
  }
  }
  
}
