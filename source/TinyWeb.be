// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;
use Encode:Url as EU;

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
    
    auto client = server.checkGetClient();
    
    if (def(client)) {
      //"got client".print();
      
      //if (true) { return(null); }
      
      return(TinyWebRequest.new(client));
    }
    return(null);
  }

}

class TinyWebRequest {

  new(TCPClient _client) {
    fields {
      TCPClient client = _client;
      List headers;
    }
  }
  
  printHeaders() {
    checkGetHeaders();
    if (def(headers)) {
      for (String header in headers) {
        header.print();
      }
    } else {
      "no headers to print".print();
    }
  }
  
  checkGetQueryString() {
    checkGetHeaders();
    if (def(headers)) {
      for (String header in headers) {
        if (header.begins("GET ")) {
          auto ll = header.split(" ");
          String qs = ll[1];
          //"found qs".print();
          //qs.print();
          return(qs);
        }
      }
    }
    return(null);
  }
  
  checkGetHeaders() List {
    if (def(headers)) {
      return(headers); //once per request
    }
    headers = List.new();
    for (Int i = 0;i < 30;i++=) {
    String line = client.checkGetPayload("\n");
    if (TS.notEmpty(line)) {
      //"got line".print();
      //line.print();
      headers += line;
      if (line == "\r\n") {
        //"got end of headers".print();
        return(headers);
      }
    } else {
      //"got no line".print();
    }
    }
    return(null);
  }
  
  close() {
    client.close();
  }
  
}