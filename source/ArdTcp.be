// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;
use Encode:Url as EU;

class Embedded:TCPServer {

   emit(cc_classHead) {
   """
   WiFiServer* server;
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
    server = new WiFiServer(bevp_port->bevi_int);
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
    bevl_res->client = client;
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
    }
  }
  
  new(String _host, Int _port) {
    host = _host;
    port = _port;
    opened = false;
  }
  
  open() self {
    emit(cc) {
    """
    client.connect(bevp_host->bems_toCcString().c_str(), bevp_port->bevi_int);
    if (client.connected()) {
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
    client.write(beva_line->bems_toCcString().c_str());
    """
    }
  }
  
  checkGetPayload() String {
    return(checkGetPayload(null));
  }
  
  checkGetPayload(String endmark) String {
    emit(cc) {
    """
    unsigned long currentTime = millis();
    unsigned long previousTime = 0; 
    long timeoutTime = 2000;
    if (client) {
    """
    }
    String payload = String.new();
    Int chari = Int.new();
    String chars = String.new(1);
    chars.setCodeUnchecked(0, 32);
    chars.size.setValue(1);
    Int zero = 0;
    emit(cc) {
    """                          
      currentTime = millis();
      previousTime = currentTime;
      while (client.connected() && currentTime - previousTime <= timeoutTime) {
        currentTime = millis();         
        if (client.available()) {      
          char c = client.read(); 
          //Serial.write(c);  
          bevl_chari->bevi_int = c;
          """
          }
          //("got int " + chari).print();
          //? check for -1 and 255 here too?
          chars.setCodeUnchecked(zero, chari);
          //("got char").print();
          //chars.print();
          payload += chars;
          if (def(endmark) && payload.ends(endmark)) {
            //"got endmark".print();
            //payload.print();
            return(payload);
          }
emit(cc) {
"""        
        }
      }
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
