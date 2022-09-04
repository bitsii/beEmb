// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;

use Embedded:TCPServer;
use Embedded:TCPClient;
use Embedded:TinyWeb;
use Embedded:TinyWebRequest;

class TinyWeb {

  new() self {
    port = 80;
  }
  
  new(Int _port) self {
    fields {
      Int port = _port;
      TCPServer server;
    }
  }
  
  start() {
    server = TCPServer.new(port);
    server.start();
  }
  
  checkGetRequest() TinyWebRequest {
    
    if (def(server)) {
      auto client = server.checkGetClient();
      
      if (def(client)) {
        //"got client".print();
        
        //if (true) { return(null); }
        
        return(TinyWebRequest.new(client));
      }
    }
    return(null);
  }

}

class TinyWebRequest {

  new(TCPClient _client) {
    fields {
      TCPClient client = _client;
    }
  }
  
  checkGetQueryString(String line) {
    for (Int i = 0;i < 30;i++=) {
    line = client.checkGetPayload(line, "\n");
      if (TS.notEmpty(line)) {
        //"got line".print();
        //line.print();
        if (line.begins("GET ")) {
          auto ll = line.split(" ");
          String qs = ll[1];
        }
        if (line == "\r\n") {
          //"got end of headers".print();
          break;
        }
      } else {
        //"got no line".print();
      }
    }
    return(qs);
  }
  
  close() {
    client.close();
  }
  
}
