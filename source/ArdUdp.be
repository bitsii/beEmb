// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;

/*
Will be needed in BEAR_Imports.cpp
#include "lwip/udp.h"
#include "lwip/igmp.h"
#define SSDP_MULTICAST_ADDR 239, 255, 255, 250
#define SSDP_PORT         1989

and this in BEAR_Imports.hpp
#include <WiFiUdp.h>
*/

class Embedded:Udp {

  emit(cc_classHead) {
  """
    WiFiUDP Udp;  
  """
  }

  new() self {
  
  }
  
  start() self {
    emit(cc) {
    """
    ip_addr_t ifaddr;
    ifaddr.addr = WiFi.localIP();
    ip_addr_t multicast_addr;
    multicast_addr.addr = (uint32_t) SSDP_MULTICAST_ADDR;
    if (igmp_joingroup(&ifaddr, &multicast_addr) != ERR_OK ) {
      Serial.println("SSDP failed to join igmp group");
    } else {
      Serial.println("JOINED");
    }
    
    Udp.beginMulticast(WiFi.localIP(), IPAddress(SSDP_MULTICAST_ADDR), SSDP_PORT);
    """
    }
  }
  
  checkGetRequest() Embedded:UDPRequest {
    Embedded:UDPRequest resm;
    Int rport;
    String rip;
    String res;
    emit(cc) {
    """
    char incomingPacket[255];
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
    // receive incoming UDP packets
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
      //Serial.printf("UDP packet contents: %s\n", incomingPacket);
      bevl_res = new BEC_2_4_6_TextString(std::string(incomingPacket));
      bevl_rip = new BEC_2_4_6_TextString(std::string(Udp.remoteIP().toString().c_str()));
      bevl_rport = new BEC_2_4_3_MathInt(Udp.remotePort());
    }
    }
    """
    }
    if (TS.notEmpty(res)) {
      //"res notempty".print();
      emit(cc) {
      """
      bevl_resm = new BEC_2_8_10_EmbeddedUDPRequest(Udp.remoteIP(), Udp.remotePort());
      """
      }
      resm.inputContent = res;
      resm.remoteAddress = rip;
      resm.remotePort = rport;
    }
    return(resm);
  }
  
}

class Embedded:UDPRequest {

  emit(cc_classHead) {
  """
    WiFiUDP bevi_udp;
    IPAddress bevi_rip;
    uint16_t bevi_rport;
    
    BEC_2_8_10_EmbeddedUDPRequest() { 
#ifdef BEDCC_SGC
     BEC_2_6_6_SystemObject** bevls_stackRefs[0] = { };
     BECS_StackFrame bevs_stackFrame(bevls_stackRefs, 0, this);
#endif
    }
    
    BEC_2_8_10_EmbeddedUDPRequest(IPAddress abevi_rip, uint16_t abevi_rport) { 
#ifdef BEDCC_SGC
     BEC_2_6_6_SystemObject** bevls_stackRefs[0] = { };
     BECS_StackFrame bevs_stackFrame(bevls_stackRefs, 0, this);
#endif
    bevi_rip = abevi_rip;
    bevi_rport = abevi_rport;
    }
    
  """
  }
  
  new() self {
    fields {
      String inputContent;
      String remoteAddress;
      Int remotePort;
    }
  }
  
  write(String res) self {
  emit(cc) {
  """
  bevi_udp.beginPacket(bevi_rip, bevi_rport);
  bevi_udp.write(beva_res->bems_toCcString().c_str());
  bevi_udp.endPacket();
  """
  }
  }

}
