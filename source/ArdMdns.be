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
use Embedded:CommonNames as CNS;

class Embedded:Mdns {

  new(String _name, String _service, Int _port, String _protocol, Embedded:App _app) self {
    slots {
      String name =  _name;
      String service = _service;
      Int port = _port;
      String protocol = _protocol;
      Embedded:App app = _app;
    }
  }
  
  start() self {
    if (TS.isEmpty(name)) {
      "mdns needs a name".print();
      return(self);
    }
    ifNotEmit(maSvr) {
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

  getAddr(String tqname) String {
    String tqip;
    if (TS.notEmpty(tqname)) {
    emit(cc) {
      """
      #ifdef BEAR_ESP32
      IPAddress tqip = MDNS.queryHost(beq->beva_tqname->bems_toCcString().c_str());
      if (tqip != INADDR_NONE) {
        String lip = tqip.toString();
        std::string lips = std::string(lip.c_str());
        beq->bevl_tqip = new BEC_2_4_6_TextString(lips);
      }
      #endif
      """
    }
    }
    return(tqip);
  }

  getAddrDis(String name) String {
    for (Int i = 0;i < 2;i++) {
      String mrip = getAddr(name);
      if (TS.notEmpty(mrip)) {
        return(mrip);
      }
      app.delay(2);
    }
    return(CNS.undefined);
  }
  
  update() self {
  emit(cc) {
  """
  #ifdef BEAR_ESP8266
    MDNS.update();
  #endif
  """
  }
  }
  
}
