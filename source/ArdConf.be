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
      Int eelength = 4096;//4096 8192 16384 - error suggests 4096 is the limit
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
       pos = names.length.copy();
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
    //("put pos " + pos + " value " + value + " " + names[pos]).print();
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
    EEPROM.begin(bevp_eelength->bevi_int);
      """
    }
    String lbuf = String.new();
    Int pe = 0; //pos in eeprom
    Int ps = 0; //pos in string
    Int code = 0;
    Int lpos = 0;
    epread(lbuf, ps, pe, code, magic.length);
    if (TS.notEmpty(lbuf) && lbuf == magic) {
      loop {
        ps.setValue(zero);
        lbuf.length.setValue(zero);
        Int res = epread(lbuf, ps, pe, code, zero);
        if (res == us) {
          names.put(lpos, lbuf.copy());
          //("eeprom read name " + lbuf).print();
        } elseIf (res == rs) {
          values.put(lpos, lbuf.copy());
          lpos++;
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
  epread(String lbuf, Int ps, Int pe, Int code, Int rlength) Int {
    Bool ines = false;
    loop {
      emit(cc) {
        """
      beq->beva_code->bevi_int = EEPROM.read(beq->beva_pe->bevi_int);
        """
      }
      if (pe < eelength) {
          pe++;
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
          Int nlength = ((ps + 16) * 3) / 2;
          lbuf.capacitySet(nlength);
        }
        lbuf.setCodeUnchecked(ps, code);
        ps++;
        lbuf.length.setValue(ps);
        if (ines) {
          ines = false;
        }
        //check length
        if (rlength > zero && lbuf.length >= rlength) {
          return(rlength);
        }
        if (lbuf.length >= maxsz) {
          return(gs);//should not happen, its broke
        }
      }
    }
  }

  save() {
    //write while iterating, no copy
    //cr for kv split nl for new pair term with empty pair
    //just has to fit in the thing, never need to know length

    //begin
    emit(cc) {
      """
    EEPROM.begin(bevp_eelength->bevi_int);
      """
    }
    //global int for position
    Int pe = 0; //pos in eeprom
    Int ps = 0; //pos in string
    Int css = 0; //current string length
    Int code = 0;

    epwrite(magic, css, ps, pe, code, false);
    for (Int lpos = 0;lpos < names.length;lpos++) {
      String name = names.get(lpos);
      String value = values.get(lpos);
      if (TS.notEmpty(name) && TS.notEmpty(value)) {
        if (name.length < maxsz && value.length < maxsz) {
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
    css.setValue(ws.length);
    for (ps.setValue(zero);ps < css;ps++) {
        if (pe < eelength) {
          ws.getCode(ps, code);
          if (code == es || code == gs || code == us || code == rs) {
            unless (noes) {
              emit(cc) {
                  """
                EEPROM.write(beq->beva_pe->bevi_int, bevp_es->bevi_int);
                  """
              }
              pe++;
              if (pe >= eelength) {
                "Out of eeprom space".print();
                return(self);
              }
            }
          }
          emit(cc) {
              """
            EEPROM.write(beq->beva_pe->bevi_int, beq->beva_code->bevi_int);
              """
          }
          pe++;
        } else {
          "Out of eeprom space".print();
          return(self);
        }
      }
      return(self);
    }

}
