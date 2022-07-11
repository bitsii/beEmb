// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;
use Encode:Url as EU;

class Embedded:SerServer {
  
  new() self {
    fields {
      Int baud = 115200;
    }
  }
  
  start() {
    emit(cc) {
    """
    Serial.begin(bevp_baud->bevi_int);
    """
    }
  }
  
  write(String line) self {
    emit(cc) {
    """
    Serial.write(beva_line->bems_toCcString().c_str());
    """
    }
  }
  
  checkGetPayload(String payload, String endmark) String {
    emit(cc) {
    """
    unsigned long currentTime = millis();
    unsigned long previousTime = 0; 
    long timeoutTime = 2000;
    """
    }
    payload.clear();
    unless (self.available) {
      //"nothing to read".print();
      return(payload);
    }
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
      while (currentTime - previousTime <= timeoutTime) {
        currentTime = millis();         
        if (Serial.available()) {      
          char c = Serial.read(); 
          bevl_chari->bevi_int = c;
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
        }
      }
    """
    }
    //if (TS.notEmpty(payload)) {
    //"got serial, payload".print();
    //payload.print();
    //}
    return(payload);
  }
  
  availableGet() Bool {
    emit(cc) {
    """
    if (Serial.available()) {
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
  
}
