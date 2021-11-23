// Copyright 2016 The Brace Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;

class EmbeddedTest:TestBlink {
   
   main() {
     fields {
       auto app = Embedded:App.new();
       auto pin = 2;
       auto delay = 2000;
       auto hlog = "in handleLoop";
     }
     app.plugin = self;
   }
   
   startLoop() {
     "in startLoop".print();
     app.pinModeOutput(pin);
   }
   
   handleLoop() {
     hlog.print();
     app.delay(delay);
     app.digitalWriteHigh(pin);
     app.delay(delay);
     app.digitalWriteLow(pin);
   }
   
}
