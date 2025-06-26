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

class Embedded:Ehd {  //EHomeDevice
  new(String _etp, String _ina, String _wada) {
    fields {
      String etp = _etp; //sw
      String ina = _ina; //unique instance name
      String wada = _wada; //http url by ip (web address)
    }
  }
}
