// Copyright 2021 The Bennt Embed Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;
use Encode:Url as EU;

class Embedded:WebServer {

   emit(cc_classHead) {
   """
   WiFiServer* server;
   """
   }

  //server start() handleWeb(request) checkHandleWeb()- input and output incrementally, when ready do, try, timeout

  //request inputContent, outputContent, queryString, uri
  
  default() self { 
    fields {
      any app;
      Int port = 80;
    }
  }
  
  new(_app) self {
    app = _app;
  }
  
  start() {
    emit(cc) {
    """
    server = new WiFiServer(bevp_port->bevi_int);
    server->begin();
    """
    }
  }
  
  checkHandleWeb() {
    
    emit(cc) {
    """
    unsigned long currentTime = millis();
    unsigned long previousTime = 0; 
    long timeoutTime = 2000;
    WiFiClient client = server->available();
    if (client) { 
    """
    }
    
    List headers = List.new();
    String line = String.new();
    Int chari = Int.new();
    String chars = String.new(1);
    chars.setCodeUnchecked(0, 32);
    chars.size.setValue(1);
    Int zero = 0;
    Int ten = 10;
    Int one = 1;
    Int thirteen = 13;
    
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
          chars.setCodeUnchecked(zero, chari);
          //("got char").print();
          //chars.print();
          if(chari == ten) {
            "got eol, line".print();
            line.print();
            //line.size.print();
            if (line.size < one) {
              //"got empty line".print();
              app.delay(one);
              auto request = Embedded:WebRequest.new(headers);
              //"doing ws handleweb".print();
              handleWeb(request);
              emit(cc) {
              """
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println("Connection: close");
              client.println();
              """
              }
              String oc = request.outputContent;
              if (def(oc)) {
                emit(cc) {
                """
                client.println(bevl_oc->bems_toCcString().c_str());
                """
                }
              }
              List ocl = request.outputContents;
              if (def(ocl)) {
                for (oc in ocl) {
                  emit(cc) {
                  """
                  client.println(bevl_oc->bems_toCcString().c_str());
                  """
                  }
                }
              } else {
               "no ocl".print();
              }
            } else {
              //"got line".print();
              //line.print();
              headers += line;
            }
            line = String.new();
          } elseIf (chari != thirteen) {
            line += chars;
          }
          
emit(cc) {
"""        
        }
      }
    }
    if (client) {  
      client.stop();
    }
    """
    }
  }
  
  handleWeb(request) {
    "in ws handleweb".print();
    app.handleWeb(request);
    //send out response (was set into request)
  }
  
}

class Embedded:WebRequest {

  //request inputContent, outputContent, queryString, uri
  new() self {
    fields {
      String outputContent;
      List outputContents;
    }
  }
  
  new(List _headers) self {
    fields {
      List headers = _headers;
      Map params;
    }
  }
  
  popParams() {
    if (undef(params)) {
      params = Map.new();
      for (String h in headers) {
        //("h is " + h).print();
        if (h.begins("GET ")) {
          auto ll = h.split(" ");
          if (ll.size == 3) {
            //("got ll 1 " + ll[1]).print();
            String ps = ll[1];
            //"doing find".print();
            Int qp = ps.find("?");
            //"find done".print();
            if (def(qp) && qp >= 0 && qp + 1 < ps.size--) {
              //"doing subs".print();
              ps = ps.substring(qp + 1, ps.size);
              //("ps " + ps).print();
              ll = ps.split("&");
              for (String llp in ll) {
                //("llp " + llp).print();
                auto dp = llp.split("=");
                if (dp.length > 0) {
                 String k = dp[0];
                 //("k " + k).print();
                }
                if (dp.length > 1) {
                 String v = dp[1];
                 //("v " + v).print();
                } else {
                 v = null;
                }
                if (TS.notEmpty(k)) {
                  k = EU.decode(k);
                  //("keud " + k).print();
                  if (TS.notEmpty(v)) {
                    v = EU.decode(v);
                    //("veud " + v).print();
                  }
                  params.put(k, v);
                }
              }
            } else {
              //"no subs".print();
            }
          }
        }
      }
    }
  }
  
  getParameter(String name) String {
    popParams();
    return(params.get(name));
  }
  
}
