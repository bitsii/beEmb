/*
 * Copyright (c) 2021-2023, the Bennt Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use IO:File:Path;
use IO:File;

use System:Parameters;
use Encode:Hex as Hex;

use class Embedded:Utils {

     new() self {
       slots {
          IO:Log log;
        }
        log = IO:Logs.get(self);
        IO:Logs.turnOnAll();
     }

     main() {
      try {
        log.log("In Embedded:Utils main");
        Parameters params = Parameters.new(System:Process.new().args);
        String cmd = params.getFirst("cmd");
        if (TS.isEmpty(cmd)) {
          log.log("no cmd");
        } else {
          if (cmd == "enhex") {
            enhex(params);
          } else {
            log.log("unknown cmd " + cmd);
          }
        }
      } catch (any e) {
        log.elog("fail in Embedded:Utils main", e);
      }
    }

    enhex(Parameters params) {
      for (String p in params.get("enhex")) {
        String ph = Hex.encode(p);
        log.log(p);
        log.log(ph);
      }
    }
     
}

