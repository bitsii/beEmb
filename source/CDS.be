// Copyright 2021 The Bennt Embed Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;

/*
Will be needed in BEAR_Imports.cpp

//for CDS.be
#include "lwip/udp.h"
#include "lwip/igmp.h"
#define SSDP_MULTICAST_ADDR 239, 255, 255, 250
#define SSDP_PORT         3200

and this in BEAR_Imports.hpp

//for CDS.be
#include <WiFiUdp.h>
*/

class Embedded:Cds {

  emit(cc_classHead) {
  """
    WiFiUDP Udp;  
  """
  }

  new() self {
    fields {
      String id;
    }
  }
  
  start() self {
    emit(cc) {
    """
    ip_addr_t ifaddr;
    ifaddr.addr = WiFi.localIP();
    ip_addr_t multicast_addr;
    multicast_addr.addr = (uint32_t) SSDP_MULTICAST_ADDR;
    if (igmp_joingroup(&ifaddr, &multicast_addr) != ERR_OK ) {
      Serial.println("Cds failed to join igmp group");
    } else {
      Serial.println("JOINED");
    }
    
    Udp.beginMulticast(WiFi.localIP(), IPAddress(SSDP_MULTICAST_ADDR), SSDP_PORT);
    """
    }
  }

  announce() self {
    //"cds announce".print();
  emit(cc) {
  """
  Udp.beginPacket(IPAddress(SSDP_MULTICAST_ADDR), SSDP_PORT);
  Udp.write(bevp_id->bems_toCcString().c_str());
  Udp.endPacket();
  """
  }
  }

}
