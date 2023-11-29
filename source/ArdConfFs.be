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
      String fn = String.new();
    }
  }

  getPos(String name) {
     Int pos = names.find(name);
     if (undef(pos)) {
       pos = names.size.copy();
       names += name;
       values += null;
       changes += null;
     }
     return(pos);
  }

  get(Int pos) String {
    return(values.get(pos));
  }

  put(Int pos, String value) {
    values.put(pos, value);
    changes.put(pos, true);
    changed = true;
    //("put pos " + pos + " value " + value + " " + names[pos]).print();
  }

  maybeSave() {
    if (changed) {
      save();
      changed = false;
    }
  }

  //for read use the file sizes
  load() {

  }

  save() {
    //write while iterating, no copy
    //sep file for n and v
    //max actually written
    //compact/reindex on read
    //no need to scan dirs, just index and exists

    //begin
    emit(cc) {
      """
    LittleFS.begin();
      """
    }
    for (Int lpos = 0;lpos < names.size;lpos++=) {
      String name = names.get(lpos);
      String value = values.get(lpos);
      Bool change = changes.get(lpos);
      if (def(change) && change) {
        if (TS.notEmpty(name) && TS.notEmpty(value)) {
            //epwrite(name, css, ps, pe, code, false);
            fn.clear();
            fn += bedn += lpos.toString();
            emit(cc) {
              """
              File fhn = LittleFS.open(bevp_fn->bems_toCcString().c_str(), "w");
              if (!fhn) {
                  Serial.println("file open failed");
              } else {
                const uint8_t* dataPointern = beq->bevl_name->bevi_bytes.data();
                fhn.write(dataPointern, beq->bevl_name->bevp_size->bevi_int);
                fhn.close();
              }
              """
            }
            //epwrite(value, css, ps, pe, code, false);
            fn.clear();
            fn += bedv += lpos.toString();
            emit(cc) {
              """
              File fhv = LittleFS.open(bevp_fn->bems_toCcString().c_str(), "w");
              if (!fhv) {
                  Serial.println("file open failed");
              } else {
                const uint8_t* dataPointerv = beq->bevl_value->bevi_bytes.data();
                fhv.write(dataPointerv, beq->bevl_value->bevp_size->bevi_int);
                fhv.close();
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
            const char* fnn = bevp_fn->bems_toCcString().c_str();
            if (LittleFS.exists(fnn)) {
               LittleFS.remove(fnn);
            }
            """
          }
          fn.clear();
          fn += bedv += lpos.toString();
          emit(cc) {
            """
            const char* fnv = bevp_fn->bems_toCcString().c_str();
            if (LittleFS.exists(fnv)) {
               LittleFS.remove(fnv);
            }
            """
          }
        }
      }
    }
    emit(cc) {
      """
    LittleFS.end();
      """
    }
  }

}
