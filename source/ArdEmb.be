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
      delay(beva_millis->bevi_int);
      """
     }
   }

   wdtFeed() {
     emit(cc) {
      """
      ESP.wdtFeed();
      """
     }
   }

   wdtDisable() {
     emit(cc) {
      """
      ESP.wdtDisable();
      //*((volatile uint32_t*) 0x60000900) &= ~(1); // Hardware WDT OFF
      """
     }
   }

   wdtEnable(Int timeout) {
     emit(cc) {
      """
      //*((volatile uint32_t*) 0x60000900) |= 1; // Hardware WDT ON
      ESP.wdtEnable(beva_timeout->bevi_int);
      """
     }
   }

   yield() {
     emit(cc) {
      """
      yield();
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
     uint8_t pin = (uint8_t) beva_pin->bevi_int;
     uint8_t value = (uint8_t) beva_value->bevi_int;
     analogWrite(pin,value);
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

   strToInt(String str) Int {
     //the existing one is "too much"
     Int res = Int.new();
     emit(cc) {
       """
       bevl_res->bevi_int = atoi(beva_str->bems_toCcString().c_str());
       """
     }
     return(res);
   }

   intToStr(Int int) String {
     //the existing one is "too much"
     //THIS IS NOT RELIABLE FOR SOME REASON
     String res;
     emit(cc) {
       """
       char buffer[20];
       itoa(beva_int->bevi_int,buffer,10);
       std::string ints = std::string(buffer);
       bevl_res = new BEC_2_4_6_TextString(ints);
       """
     }
     return(res);
   }

   maybeGc() {
   emit(cc) {
   """
   BECS_Runtime::doGc();
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

  macAddressGet() String {
    String macAddress;
    emit(cc) {
      """
      String mac = WiFi.macAddress();
      std::string macs = std::string(mac.c_str());
      bevl_macAddress = new BEC_2_4_6_TextString(macs);
      """
    }
    return(macAddress);
  }

  scanNetworks() List {
    List networks = List.new();
    String network;
    emit(cc) {
      """
      int numberOfNetworks = WiFi.scanNetworks();

      for(int i =0; i<numberOfNetworks; i++){
        String ssid = WiFi.SSID(i);
        std::string ssids = std::string(ssid.c_str());
        bevl_network = new BEC_2_4_6_TextString(ssids);
        bevl_networks->bem_addValue_1(bevl_network);
      }

      """
    }

    return(networks);
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

class Embedded:Config {

  new() {
    fields {
      Int eesize = 8192;//8192 16384
      Int maxsz = 128;//how big we let a name or value be
      List names = List.new();
      List values = List.new();
      Bool changed = false;
      String magic = "braceEmb";
    }
    slots {
      Int zero = 0;
      Int one = 1;
      Int es = 27; //"escape" a control not as a control is next
      String ess = String.codeNew(es);
      Int gs = 29; //"group separator" at end
      String gss = String.codeNew(gs);
      Int us = 31; //"unit separator" between name value
      String uss = String.codeNew(us);
      Int rs = 30; //"record separator" betw entries
      String rss = String.codeNew(rs);
    }
  }

  getPos(String name) {
     Int pos = names.find(name);
     if (undef(pos)) {
       pos = names.size.copy();
       names += name;
       values += null;
     }
     return(pos);
  }

  get(Int pos) String {
    return(values.get(pos));
  }

  put(Int pos, String value) {
    values.put(pos, value);
    changed = true;
  }

  maybeSave() {
    if (changed) {
      save();
      changed = false;
    }
  }

  load() {
    //begin
    emit(cc) {
      """
    EEPROM.begin(bevp_eesize->bevi_int);
      """
    }
    String lbuf = String.new();
    Int pe = 0; //pos in eeprom
    Int ps = 0; //pos in string
    Int code = 0;
    Int lpos = 0;
    epread(lbuf, ps, pe, code, magic.size);
    if (TS.notEmpty(lbuf) && lbuf == magic) {
      loop {
        ps.setValue(zero);
        lbuf.size.setValue(zero);
        Int res = epread(lbuf, ps, pe, code, zero);
        if (res == us) {
          names.put(lpos, lbuf.copy());
          //("eeprom read name " + lbuf).print();
        } elseIf (res == rs) {
          values.put(lpos, lbuf.copy());
          lpos++=;
          //("eeprom read value " + lbuf).print();
        } elseIf (res == gs) {
          "read all done".print();
          break;
        } else {
          ("read fail " + res).print();
          break;
        }
      }
    } else {
      "bad magic".print();
    }
    emit(cc) {
      """
    EEPROM.commit();
      """
    }
  }

  //res
  epread(String lbuf, Int ps, Int pe, Int code, Int rsize) Int {
    Bool ines = false;
    loop {
      emit(cc) {
        """
      beva_code->bevi_int = EEPROM.read(beva_pe->bevi_int);
        """
      }
      if (pe < eesize) {
          pe++=;
      } else {
        "Out of eeprom space".print();
        return(gs);
      }
      if (code == es && ines!) {
        ines = true;
      } else {
        if (code == rs || code == us || code == gs) {
          unless (ines) {
            return(code);
          }
        }
        //add to string
        if (ps >= lbuf.capacity) {
          Int nsize = ((ps + 16) * 3) / 2;
          lbuf.capacitySet(nsize);
        }
        lbuf.setCodeUnchecked(ps, code);
        ps++=;
        lbuf.size.setValue(ps);
        if (ines) {
          ines = false;
        }
        //check size
        if (rsize > zero && lbuf.size >= rsize) {
          return(rsize);
        }
        if (lbuf.size >= maxsz) {
          return(gs);//should not happen, its broke
        }
      }
    }
  }

  save() {
    //write while iterating, no copy
    //cr for kv split nl for new pair term with empty pair
    //just has to fit in the thing, never need to know size

    //begin
    emit(cc) {
      """
    EEPROM.begin(bevp_eesize->bevi_int);
      """
    }
    //global int for position
    Int pe = 0; //pos in eeprom
    Int ps = 0; //pos in string
    Int css = 0; //current string size
    Int code = 0;

    epwrite(magic, css, ps, pe, code, false);
    for (Int lpos = 0;lpos < names.size;lpos++=) {
      String name = names.get(lpos);
      String value = values.get(lpos);
      if (TS.notEmpty(name) && TS.notEmpty(value)) {
        if (name.size < maxsz && value.size < maxsz) {
          epwrite(name, css, ps, pe, code, false);
          //("wrote name " + name).print();
          epwrite(uss, css, ps, pe, code, true);
          epwrite(value, css, ps, pe, code, false);
          //("wrote value " + value).print();
          epwrite(rss, css, ps, pe, code, true);
        } else {
          "name or value too big to write".print();
        }
      } else {
        //"name or value too empty to write".print();
      }
    }
    epwrite(gss, css, ps, pe, code, true);
    emit(cc) {
      """
    EEPROM.commit();
      """
    }
  }

  epwrite(String ws, Int css, Int ps, Int pe, Int code, Bool noes) {
    css.setValue(ws.size);
    for (ps.setValue(zero);ps < css;ps++=) {
        if (pe < eesize) {
          ws.getCode(ps, code);
          if (code == es || code == gs || code == us || code == rs) {
            unless (noes) {
              emit(cc) {
                  """
                EEPROM.write(beva_pe->bevi_int, bevp_es->bevi_int);
                  """
              }
              pe++=;
              if (pe >= eesize) {
                "Out of eeprom space".print();
                return(self);
              }
            }
          }
          emit(cc) {
              """
            EEPROM.write(beva_pe->bevi_int, beva_code->bevi_int);
              """
          }
          pe++=;
        } else {
          "Out of eeprom space".print();
          return(self);
        }
      }
      return(self);
    }

}

class Embedded:Files {

  default() self {
    slots {
      //String nt = String.codeNew(0);
    }
  }
  
  open() {
   emit(cc) {
   """
   SPIFFS.begin();
   """
   }
  }
  
  write(String name, String data) {
    //String fname = name + nt;
    emit(cc) {
    """
    File f = SPIFFS.open(beva_name->bems_toCcString().c_str(), "w");
    //File f = SPIFFS.open((const char*) bevl_fname->bevi_bytes[0], "w");
    if (!f) {
        Serial.println("file open failed");
        """
        }
        throw(Exception.new("File could not be opened"));
        emit(cc) {
        """
    } else {
      //size_t wsize = (size_t) beva_data->bevp_size->bevi_int;
      //unsigned char* wbuf = &(beva_data->bevi_bytes[0]);
      //if (f.write(wbuf, wsize) == wsize) { }
      if(f.print(beva_data->bems_toCcString().c_str())) {
          //Serial.println("File was written");
      } else {
          Serial.println("File write failed");
          """
          }
          throw(Exception.new("Data could not be written"));
          emit(cc) {
          """
      }
      f.flush();
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
          throw(Exception.new("File could not be opened"));
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

