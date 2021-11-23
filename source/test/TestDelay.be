// Copyright 2016 The Brace Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;

class EmbeddedTest:TestDelay {
   
   main() {
     fields {
       auto app = Embedded:App.new();
       auto delay = 5000;
       //auto delay = 50;
       auto hlog = "in handleLoop, delay " + delay + " ms";
       auto count = 0;
     }
     app.plugin = self;
   }
   
   startLoop() {
     "in startLoop".print();
   }
   
   handleLoop() {
     if (count > 10000) {
       count = 5000;
     }
    hlog.print();
    count.print();
    count++=;
     app.delay(delay);
   }
   
}
