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

class Embedded:TCPServer {

   emit(cc_classHead) {
   """
   std::unique_ptr<WiFiServer> server;
   """
   }
  
  new(Int _port) self {
    fields {
      Int port = _port; //light 55443
    }
  }
  
  start() {
    emit(cc) {
    """
    server = std::make_unique<WiFiServer>(bevp_port->bevi_int);
    server->begin();
    """
    }
  }
  
  checkGetClient() Embedded:TCPClient {
    Embedded:TCPClient res;
    emit(cc) {
    """
    WiFiClient client = server->available();
    if (client) {
    """
    }
    res = Embedded:TCPClient.new();
    res.opened = true;
    emit(cc) {
    """
    beq->bevl_res->client = client;
    client.setTimeout(beq->bevl_res->bevp_streamTimeout->bevi_int);
    }
    """
    }
    return(res);
  }
  
}

class Embedded:TCPClient {

emit(cc_classHead) {
"""

WiFiClient client;

"""
}

  new() self {
    fields {
      String host;
      Int port;
      Bool opened;
      Int connectTimeout = 200;
      Int streamTimeout = 20; //was 2
    }
  }
  
  new(String _host, Int _port) {
    host = _host;
    port = _port;
    opened = false;
    connectTimeout = 200;
    streamTimeout = 20; //was 2
  }
  
  open() self {
    emit(cc) {
    """
    //client.setTimeout, milliseconds, default 1000. works for con and stream
    client.setTimeout(bevp_connectTimeout->bevi_int);
    client.connect(bevp_host->bems_toCcString().c_str(), bevp_port->bevi_int);
    if (client.connected()) {
      client.setTimeout(bevp_streamTimeout->bevi_int);
    """
    }
    opened = true;
    emit(cc) {
    """
    } else {
      //Serial.println("connection failed");
    }
    """
    }
    return(self);
  }
  
  write(String line) self {
    emit(cc) {
    """
    client.write(beq->beva_line->bems_toCcString().c_str());
    """
    }
  }
  
  checkGetPayload(String payload, String endmark) String {
    emit(cc) {
    """
    unsigned long currentTime = millis();
    unsigned long previousTime = 0; 
    long timeoutTime = 2000;
    if (client) {
    """
    }
    payload.clear();
    Int chari = Int.new();
    String chars = String.new(1);
    chars.setCodeUnchecked(0, 32);
    chars.size.setValue(1);
    Int zero = 0;
    if (def(endmark) && endmark.size > 1) {
      "only one char endmarks supported".print();
      return(payload);
    }
    emit(cc) {
    """                          
      currentTime = millis();
      previousTime = currentTime;
      while (client.connected() && currentTime - previousTime <= timeoutTime) {
        previousTime = currentTime;
        currentTime = millis();
        if (client.available()) {
          char c = client.read(); 
          //Serial.write(c);
          beq->bevl_chari->bevi_int = c;
          """
          }
          //("got int " + chari).print();
          //? check for -1 and 255 here too?
          chars.setCodeUnchecked(zero, chari);
          //("got char").print();
          //chars.print();
          payload += chars;
          //if (def(endmark) && payload.ends(endmark)) { }
          if (def(endmark) && chars == endmark) {
            //"got endmark".print();
            //payload.print();
            return(payload);
          }
emit(cc) {
"""        
        } else {
          //Serial.println("not available");
        }
      }
    } else {
      //Serial.println("no client");
    }
    """
    }
    //if (TS.notEmpty(payload)) {
    //"got request, payload".print();
    //payload.print();
    //}
    return(payload);
  }
  
  connectedGet() Bool {
    emit(cc) {
    """
    if (client && client.connected()) {
     """
     }
     return(true);
     emit(cc) {
     """
     }
     """
     }
     return(false);
  }  
  
  availableGet() Bool {
    emit(cc) {
    """
    if (client && client.connected() && client.available()) {
     """
     }
     return(true);
     emit(cc) {
     """
     }
     """
     }
     return(false);
  }  

  remoteIpGet() String {
    String ip;
    emit(cc) {
      """
      String lip = client.remoteIP().toString();
      std::string lips = std::string(lip.c_str());
      beq->bevl_ip = new BEC_2_4_6_TextString(lips);
      """
    }
    return(ip);
  }
  
  close() {
    emit(cc) {
    """
    if (client) {  
      client.stop();
    }
    """
    }
    opened = false;
  }

}
