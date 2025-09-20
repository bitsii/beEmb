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

use Embedded:CommonNames as CNS;

use Embedded:Wifi;

class Embedded:Dfis {

  new(_ash) self {
    slots {
      Embedded:AppShell ash = _ash;
      Int nextOutset = 0;
    }
  }

  start() {

  }

  teeOutset() {
    nextOutset = ash.nowup + 6000;
  }

  handleLoop() {
    if (nextOutset > 0 && ash.nowup > nextOutset) {
      "would outset".print();
    }
  }

}
