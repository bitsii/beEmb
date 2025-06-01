/*
 * Copyright (c) 2021-2023, the Brace Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

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
      //size_t wlength = (size_t) beva_data->bevp_length->bevi_int;
      //unsigned char* wbuf = &(beva_data->bevi_bytes[0]);
      //if (f.write(wbuf, wlength) == wlength) { }
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
      chars.length.setValue(1);
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
