// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;

class Embedded:Udp {

  emit(cc_classHead) {
  """
    WiFiUDP Udp;
    char incomingPacket[255];  
  """
  }

  new() self {
  
  }
  
  start() self {
    emit(cc) {
    """
     //UdpContext* _server = new UdpContext;
     //_server->ref();
  
    ip_addr_t ifaddr;
    ifaddr.addr = WiFi.localIP();
    ip_addr_t multicast_addr;
    multicast_addr.addr = (uint32_t) SSDP_MULTICAST_ADDR;
    if (igmp_joingroup(&ifaddr, &multicast_addr) != ERR_OK ) {
      Serial.println("SSDP failed to join igmp group");
    } else {
      Serial.println("JOINED");
    }
    
    //just do plain udp listen
    Udp.beginMulticast(WiFi.localIP(), IPAddress(SSDP_MULTICAST_ADDR), SSDP_PORT);
    //UDP.begin(SSDP_PORT);
    //if (!_server->listen(IP_ADDR_ANY, SSDP_PORT)) {
    //  Serial.println("Listen Fail");
    //} else {
    //  Serial.println("Listen OK");
    //}
    
    """
    }
  }
  
  checkGetPayload() String {
    String res;
    emit(cc) {
    """
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
    }
    """
    }
    return(res);
  }
  
  
}