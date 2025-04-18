/*
 * Copyright (c) 2024-2025, the Beysant Embedded Authors.
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
  new(String _ondid, String _ipos, String _spass) {
    fields {
      String ondid = _ondid;
      String ipos = _ipos;
      String spass = _spass;
    }
  }
}
