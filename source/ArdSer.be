/*
 * Copyright (c) 2021-2023, the Brace Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

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

  enableDebug() {
   emit(cc) {
     """
     Serial.setDebugOutput(true);
     """
   }

  }
  
  write(String line) self {
    emit(cc) {
    """
    Serial.write(beq->beva_line->bems_toCcString().c_str());
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
        previousTime = currentTime;
        currentTime = millis();         
        if (Serial.available()) {      
          char c = Serial.read(); 
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
