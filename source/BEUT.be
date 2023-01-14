// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

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

