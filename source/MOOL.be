/*
 * Copyright (c) 2024-2025, the Beysant Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:AppShell;
use Embedded:Config;

//
//https://github.com/espressif/arduino-esp32/blob/master/libraries/Matter/examples/MatterOnOffLight/MatterOnOffLight.ino
//put in BEAR_Imports.hpp for esp32
//#include <Matter.h>
//

use Embedded:CommonNames as CNS;

class Embedded:MatterOnOffLight {

emit(cc_classHead) {
"""
std::unique_ptr<MatterOnOffLight> bevi_matr;
"""
}

  new(Bool _state) self {
    slots {
      Bool state = _state;
    }
  }

  start() {
    emit(cc) {
      """
      bevi_matr = std::make_unique<MatterOnOffLight>();
      """
    }
  }

}
