// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;

class Embedded:App {
   
   default() self { 
     fields {
       any plugin;
     }
   }
   
   handleWeb(request) {
     //"in app handleweb".print();
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
      //ESP.wdtFeed();
      //ESP.wdtDisable();
      //ESP.wdtEnable(1000);
      //yield();
      ESP.wdtFeed();
      delay(beva_millis->bevi_int);
      //yield();
      """
     }
   }

   feed() {
     emit(cc) {
      """
      //ESP.wdtFeed();
      //ESP.wdtDisable();
      //ESP.wdtEnable(1000);
      //yield();
      ESP.wdtFeed();
      //yield();
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
   
   uptime(Int millis) Int {
     emit(cc) {
     """
     beva_millis->bevi_int = millis();
     """
     }
     return(millis);
   }
   
   pinModeOutput(Int pin) {
     emit(cc) {
     """
     //pinMode(255, OUTPUT);
     //analogWrite(255, 0);
     //analogWrite(255, 10);
     pinMode(beva_pin->bevi_int,OUTPUT);
     """
     }
   }
   
   analogWrite(Int pin, Int value) {
     emit(cc) {
     """
     //ESP.wdtDisable();
     uint8_t pin = (uint8_t) beva_pin->bevi_int;
     uint8_t value = (uint8_t) beva_value->bevi_int;
     analogWrite(pin,value);
     //ESP.wdtEnable(1000);
     //ESP.wdtFeed();
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
        //Serial.println("AP Started");
        String lip = WiFi.softAPIP().toString();
        std::string lips = std::string(lip.c_str());
        bevp_localIP = new BEC_2_4_6_TextString(lips);
        bevp_up = BECS_Runtime::boolTrue;
      }
      else
      {
        //Serial.println("AP Start Failed!");
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
      //Serial.print("Connected, IP address:\t");
      Serial.println(WiFi.localIP()); 
      String lip = WiFi.localIP().toString();
      std::string lips = std::string(lip.c_str());
      bevp_localIP = new BEC_2_4_6_TextString(lips);
      bevp_up = BECS_Runtime::boolTrue;
    } else {
      //Serial.println("no luck connecting to wifi");
      bevp_up = BECS_Runtime::boolFalse;
    }
    """
    }
    //("Connected to " + ssid).print();
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
        //Serial.println("wifi no more connected");
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
    return(read(name, String.new()));
  }
  
    read(String name, String data) String {
    
      data.clear();
      Int chari = Int.new();
      String chars = String.new(1);
      chars.setCodeUnchecked(0, 32);
      chars.size.setValue(1);
      Int zero = 0;
      Int n1 = -1;
      Int n255 = 255;
      
      emit(cc) {
      """
      File f = SPIFFS.open(beva_name->bems_toCcString().c_str(), "r");
      if (!f) {
          Serial.println("file open failed");
          """
          }
          //throw(Exception.new("File could not be opened"));
          return(data);
          emit(cc) {
          """
      } else {
          while (f.available()) {   
              char c = f.read(); 
              bevl_chari->bevi_int = c;
              """
              }
              if (chari == n1 || chari == n255) {
                //our file is broke/ended
                emit(cc) {
                """
                Serial.println("file broken");
                f.close();
                """
                }
                return(data);
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

class Embedded:Update {

     emit(cc_classHead) {
   """
BearSSL::PublicKey *signPubKey = nullptr;
BearSSL::HashSHA256 *hash;
BearSSL::SigningVerifier *sign;
   """
     }

  signKey(String cert) {
    emit(cc) {
      """
signPubKey = new BearSSL::PublicKey(beva_cert->bems_toCcString().c_str());
hash = new BearSSL::HashSHA256();
sign = new BearSSL::SigningVerifier(signPubKey);
      """
    }
  }

  updateFromUrl(String url) {

    emit(cc) {
     """
     if (signPubKey != nullptr) {
       Serial.println("setting update signature");
       Update.installSignature(hash, sign);
     }
     WiFiClient client;
     t_httpUpdate_return ret = ESPhttpUpdate.update(client, beva_url->bems_toCcString().c_str());
     """
    }

  }

}

