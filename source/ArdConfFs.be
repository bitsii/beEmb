/*
 * Copyright (c) 2021-2023, the Beysant Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Text:Strings as TS;
use System:Exception;

class Embedded:Config {

  new() {
    fields {
      Bool changed = false;
    }
    slots {
      List names = List.new();
      List values = List.new();
      List changes = List.new();
      String bedn = "/bedn/";
      String bedv = "/bedv/";
      String bedmax = "/bedmax";
      Int lastBmx = 0;
    }
  }

  getPos(String name) {
     Int pos = names.find(name);
     if (undef(pos)) {
      for (Int i = 0;i < names.length;i++) {
        if (undef(names.get(i))) {
          pos = i;
          names.put(pos, name);
          values.put(pos, null);
          changes.put(pos, null);
          break;
        }
      }
     }
     if (undef(pos)) {
       pos = names.length.copy();
       names.put(pos, name);
       values.put(pos, null);
       changes.put(pos, null);
     }
     //("pos " + pos + " for name " + name).print();
     return(pos);
  }

  get(Int pos) String {
    //("get pos " + pos).print();
    return(values.get(pos));
  }

  put(Int pos, String value) {
    //("put pos " + pos + " value " + value + " " + names[pos]).print();
    values.put(pos, value);
    changes.put(pos, true);
    changed = true;
  }

  maybeSave() {
    if (changed) {
      changed = false;
      save();
    }
  }

  //for read use the file lengths
  load() {
    //begin
    //"loading".print();
    emit(cc) {
      """
#ifdef BEAR_ESP8266
    SPIFFS.begin();
#endif
#ifdef BEAR_ESP32
    SPIFFS.begin(true);
#endif
      """
    }
    Int fsz = Int.new();
    emit(cc) {
      """
      const char* fnx = bevp_bedmax->bems_toCcString().c_str();
      if (SPIFFS.exists(fnx)) {
        File fhx = SPIFFS.open(fnx, "r");
        if (!fhx) {
            Serial.println("file open failed");
        } else {
          beq->bevl_fsz->bevi_int = fhx.size();
          """
        }
        String bmxs = String.new(fsz);
        bmxs.length.setValue(fsz);
        //("bmxs length " + bmxs.length).print();
    emit(cc) {
      """
          uint8_t* dataPointerx = beq->bevl_bmxs->bevi_bytes.data();
          fhx.read(dataPointerx, beq->bevl_bmxs->bevp_length->bevi_int);
          fhx.close();
        }
      }
      """
    }
    if (TS.isEmpty(bmxs) || bmxs.isInteger!) {
      //"bmxs empty".print();
      return(self);
    }
    //("bmxs " + bmxs).print();
    String fn = String.new();
    Int bmx = Int.new(bmxs);
    for (Int i = 0;i < bmx;i++) {
      //("try load " + i).print();
      bns = null;
      bvs = null;
      fn.clear();
      fn += bedn += i.toString();
      //("fn " + fn).print();
      emit(cc) {
        """
        //const char* fnn = beq->bevl_fn->bems_toCcString().c_str();
        //Serial.println(beq->bevl_fn->bems_toCcString().c_str());
        if (SPIFFS.exists(beq->bevl_fn->bems_toCcString().c_str())) {
          File fhn = SPIFFS.open(beq->bevl_fn->bems_toCcString().c_str(), "r");
          if (!fhn) {
              Serial.println("file open failed");
          } else {
            beq->bevl_fsz->bevi_int = fhn.size();
            """
          }
          String bns = String.new(fsz);
          bns.length.setValue(fsz);
      emit(cc) {
        """
            uint8_t* dataPointern = beq->bevl_bns->bevi_bytes.data();
            fhn.read(dataPointern, beq->bevl_bns->bevp_length->bevi_int);
            fhn.close();
          }
        } else {
          //Serial.println("file no exists n");
        }
        """
      }

      fn.clear();
      fn += bedv += i.toString();
      //("fn " + fn).print();
      emit(cc) {
        """
        //const char* fnv = beq->bevl_fn->bems_toCcString().c_str();
        //Serial.println(beq->bevl_fn->bems_toCcString().c_str());
        if (SPIFFS.exists(beq->bevl_fn->bems_toCcString().c_str())) {
          File fhv = SPIFFS.open(beq->bevl_fn->bems_toCcString().c_str(), "r");
          if (!fhv) {
              Serial.println("file open failed");
          } else {
            beq->bevl_fsz->bevi_int = fhv.size();
            """
          }
          String bvs = String.new(fsz);
          bvs.length.setValue(fsz);
      emit(cc) {
        """
            uint8_t* dataPointerv = beq->bevl_bvs->bevi_bytes.data();
            fhv.read(dataPointerv, beq->bevl_bvs->bevp_length->bevi_int);
            fhv.close();
          }
        } else {
          //Serial.println("file no exists v");
        }
        """
      }
      if (TS.notEmpty(bns) && TS.notEmpty(bvs)) {
        names.put(i, bns);
        values.put(i, bvs);
        changes.put(i, false);
        //("loaded " + i + " " + bns + " " + bvs).print();
      } else {
        //if (TS.isEmpty(bns)) { "bns empty".print(); }
        //if (TS.isEmpty(bvs)) { "bvs empty".print(); }
      }
    }
    lastBmx = bmx;
    emit(cc) {
      """
    SPIFFS.end();
      """
    }
    //"load done".print();
  }

  save() {
    //write while iterating, no copy
    //sep file for n and v
    //max actually written
    //no need to scan dirs, just index and exists
    //"saving".print();
    //begin
    emit(cc) {
      """
#ifdef BEAR_ESP8266
    SPIFFS.begin();
#endif
#ifdef BEAR_ESP32
    SPIFFS.begin(true);
#endif
      """
    }
    //"save looping".print();
    String fn = String.new();
    for (Int lpos = 0;lpos < names.length;lpos++) {
      String name = names.get(lpos);
      String value = values.get(lpos);
      Bool change = changes.get(lpos);
      if (def(change) && change) {
        if (TS.notEmpty(name) && TS.notEmpty(value)) {
            //("save " + lpos + " " + name + " " + value).print();
            fn.clear();
            fn += bedn += lpos.toString();
            //("fn " + fn).print();
            emit(cc) {
              """
              //Serial.println(beq->bevl_fn->bems_toCcString().c_str());
              File fhn = SPIFFS.open(beq->bevl_fn->bems_toCcString().c_str(), "w");
              if (!fhn) {
                  Serial.println("file open failed");
              } else {
                const uint8_t* dataPointern = beq->bevl_name->bevi_bytes.data();
                size_t wrn = fhn.write(dataPointern, beq->bevl_name->bevp_length->bevi_int);
                fhn.close();
                //Serial.println(wrn);
              }
              """
            }
            fn.clear();
            fn += bedv += lpos.toString();
            //("fn " + fn).print();
            emit(cc) {
              """
              //Serial.println(beq->bevl_fn->bems_toCcString().c_str());
              File fhv = SPIFFS.open(beq->bevl_fn->bems_toCcString().c_str(), "w");
              if (!fhv) {
                  Serial.println("file open failed");
              } else {
                const uint8_t* dataPointerv = beq->bevl_value->bevi_bytes.data();
                size_t wrv = fhv.write(dataPointerv, beq->bevl_value->bevp_length->bevi_int);
                fhv.close();
                //Serial.println(wrv);
              }
              """
            }
        } else {
          //"name or value too empty to write".print();
          //delete
          fn.clear();
          fn += bedn += lpos.toString();
          emit(cc) {
            """
            //const char* fnn = beq->bevl_fn->bems_toCcString().c_str();
            if (SPIFFS.exists(beq->bevl_fn->bems_toCcString().c_str())) {
               SPIFFS.remove(beq->bevl_fn->bems_toCcString().c_str());
            }
            """
          }
          fn.clear();
          fn += bedv += lpos.toString();
          emit(cc) {
            """
            //const char* fnv = beq->bevl_fn->bems_toCcString().c_str();
            if (SPIFFS.exists(beq->bevl_fn->bems_toCcString().c_str())) {
               SPIFFS.remove(beq->bevl_fn->bems_toCcString().c_str());
            }
            """
          }
        }
        changes.put(lpos, false);
      }
    }
    //save lpos as bedmax
    if (lpos != lastBmx) {
      lastBmx = lpos;
      String bmxs = lpos.toString();
      emit(cc) {
        """
        File fhn = SPIFFS.open(bevp_bedmax->bems_toCcString().c_str(), "w");
        if (!fhn) {
            Serial.println("file open failed");
        } else {
          const uint8_t* dataPointern = beq->bevl_bmxs->bevi_bytes.data();
          fhn.write(dataPointern, beq->bevl_bmxs->bevp_length->bevi_int);
          fhn.close();
        }
        """
      }
      //("save bmxs " + bmxs).print();
    }
    emit(cc) {
      """
    SPIFFS.end();
      """
    }
    //("save done").print();
    //load();
  }

}
