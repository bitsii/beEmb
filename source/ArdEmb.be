// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;
use Encode:Url as EU;

class Embedded:App {
   
   default() self { 
     fields {
       any plugin;
     }
   }
   
   handleWeb(request) {
     "in app handleweb".print();
     plugin.handleWeb(request);
   }

   startLoop() {
     plugin.startLoop();
   }
   
   handleLoop() {
     plugin.handleLoop();
   }
   
   delay(Int millis) {
     emit(cc) {
      """
      ESP.wdtFeed();
      delay(beva_millis->bevi_int);
      """
     }
   }
   
   uptime() Int {
     Int millis = Int.new();
     emit(cc) {
     """
     bevl_millis->bevi_int = millis();
     """
     }
     return(millis);
   }
   
   pinModeOutput(Int pin) {
     emit(cc) {
     """
     pinMode(beva_pin->bevi_int,OUTPUT);
     """
     }
   }
   
   digitalWriteHigh(Int pin) {
     emit(cc) {
     """
     digitalWrite(beva_pin->bevi_int,HIGH);
     """
     }
   }
   
   digitalWriteLow(Int pin) {
     emit(cc) {
     """
     digitalWrite(beva_pin->bevi_int,LOW);
     """
     }
   }
   
   restart() {
     emit(cc) {
     """
     ESP.restart();
     """
     }
   }

}

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
      Serial.println("connection failed");
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
          chars.setCodeUnchecked(zero, chari);
          //("got char").print();
          //chars.print();
          payload += chars;
          if (def(endmark) && payload.ends(endmark)) {
            "got endmark".print();
            payload.print();
            return(payload);
          }
emit(cc) {
"""        
        }
      }
    }
    """
    }
    if (TS.notEmpty(payload)) {
    "got request, payload".print();
    payload.print();
    }
    return(payload);
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
            //"got eol, line".print();
            //line.print();
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

class Embedded:Wifi {

  default() self { 
    fields {
      String mode;
      String ssid;
      String password;
      Bool up = false;
      String localIP;
    }
  }
  
  clear() {
    mode = null;
    up = false;
    localIP = null;
  }
  
  clearAll() {
    clear();
    ssid = null;
    password = null;
  }
  
  new(String _ssid, String _password) self {
    ssid = _ssid;
    password = _password;
  }
  
  startAp() {
      clear();
      mode = "ap";
      ("Starting AP " + ssid).print();
      emit(cc) {
      """
      boolean result = WiFi.softAP(bevp_ssid->bems_toCcString().c_str(), bevp_password->bems_toCcString().c_str());
      if(result == true)
      {
        Serial.println("AP Started");
        String lip = WiFi.softAPIP().toString();
        std::string lips = std::string(lip.c_str());
        bevp_localIP = new BEC_2_4_6_TextString(lips);
        bevp_up = BECS_Runtime::boolTrue;
      }
      else
      {
        Serial.println("AP Start Failed!");
        bevp_up = BECS_Runtime::boolFalse;
      }
      """
      }
    }
  
  start() {
    clear();
    mode = "station";
    ("Connecting to " + ssid).print();
    emit(cc) {
    """
    WiFi.begin(bevp_ssid->bems_toCcString().c_str(), bevp_password->bems_toCcString().c_str());
    int count = 0;
    while (WiFi.status() != WL_CONNECTED && count < 40) {
      delay(500);
      Serial.print(".");
      count++;
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("Connected, IP address:\t");
      Serial.println(WiFi.localIP()); 
      String lip = WiFi.localIP().toString();
      std::string lips = std::string(lip.c_str());
      bevp_localIP = new BEC_2_4_6_TextString(lips);
      bevp_up = BECS_Runtime::boolTrue;
    } else {
      Serial.println("no luck connecting to wifi");
      bevp_up = BECS_Runtime::boolFalse;
    }
    """
    }
  }
  
    isConnectedGet() Bool {
      unless (up && TS.notEmpty(mode) && mode == "station") {
        return(false);
      }
      Bool connected;
      emit(cc) {
      """
      if (WiFi.status() == WL_CONNECTED) {
        //Serial.println("wifi still connected");
        bevl_connected = BECS_Runtime::boolTrue;
      } else {
        Serial.println("wifi no more connected");
        bevl_connected = BECS_Runtime::boolFalse;
      }
      """
      }
      return(connected)
    }
  
  stop() {
    clear();
    emit(cc) {
    """
    WiFi.disconnect();
    """
    }
  }

}

class Embedded:Files {

  default() self { }
  
  open() {
   emit(cc) {
   """
   SPIFFS.begin();
   """
   }
  }
  
  write(String name, String data) {
    emit(cc) {
    """
    File f = SPIFFS.open(beva_name->bems_toCcString().c_str(), "w");
    if (!f) {
        //Serial.println("file open failed");
        """
        }
        throw(Exception.new("File could not be opened"));
        emit(cc) {
        """
    } else {
      if(f.print(beva_data->bems_toCcString().c_str())) {
          //Serial.println("File was written");
      } else {
          //Serial.println("File write failed");
          """
          }
          throw(Exception.new("Data could not be written"));
          emit(cc) {
          """
      }
      f.close();
    }
    """
    }
  }
  
    read(String name) String {
    
      String data = String.new();
      Int chari = Int.new();
      String chars = String.new(1);
      chars.setCodeUnchecked(0, 32);
      chars.size.setValue(1);
      Int zero = 0;
      
      emit(cc) {
      """
      File f = SPIFFS.open(beva_name->bems_toCcString().c_str(), "r");
      if (!f) {
          //Serial.println("file open failed");
          """
          }
          throw(Exception.new("File could not be opened"));
          emit(cc) {
          """
      } else {
          while (f.available()) {      
              char c = f.read(); 
              bevl_chari->bevi_int = c;
              """
              }
              chars.setCodeUnchecked(zero, chari);
              data += chars;          
    emit(cc) {
    """        
            }
            f.close();
          }
        """
        }
        return(data);
    }
  
  exists(String name) Bool {
    emit(cc) {
    """
    if (SPIFFS.exists(beva_name->bems_toCcString().c_str())) {
        """
        }
        return(true);
        emit(cc) {
        """
    } else {
        """
        }
        return(false);
        emit(cc) {
        """
    }
    """
    }
  }
  
  delete(String name) Bool {
    emit(cc) {
    """
    if (SPIFFS.remove(beva_name->bems_toCcString().c_str())) {
        """
        }
        return(true);
        emit(cc) {
        """
    } else {
        """
        }
        return(false);
        emit(cc) {
        """
    }
    """
    }
  }
  
  close() {
    emit(cc) {
    """
    SPIFFS.end();
    """
    }
  }

}
