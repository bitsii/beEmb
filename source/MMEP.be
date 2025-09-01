/*
 * Copyright (c) 2024-2025, the Brace Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Text:String;
use Text:Strings as TS;

class Embedded:Mmep {
  new(String _met, String _ondid, String _ipos, String _spass) {
    fields {
      String met = _met; //ool or dl or ecl or eclns
      String ondid = _ondid;
      String ipos = _ipos;
      String spass = _spass;
      Bool sw; //sw state, all types
      Int ct;//temp
      Int h;
      Int s;
      Int v;
      Bool inCtCh;
      Int ctLvl;
      String rip; //it's ip if known
      Int lastUp;//for rmold
    }
  }

}
