// Copyright 2016 The Brace Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;
use Text:String;
use Embedded:Files;

class EmbeddedTest:TestStuff {
   
   main() {
     fields {
       auto app = Embedded:App.new();
     }
     app.plugin = self;
   }
   
   startLoop() {
     "in startLoop".print();
   }
   
   handleLoop() {
      //handleLoopGct();
      handleLoopFiles();
   }
   
   handleLoopFiles() {
     "in hl files".print();
     Files f = Files.new();
     f.open();
     //f.delete("/hlf.txt");
     ("exists before " + f.exists("/hlf.txt")).print();
     f.write("/hlf.txt", "yo bob");
     ("exists after " + f.exists("/hlf.txt")).print();
     "reading file".print();
     String data = f.read("/hlf.txt");
     "printing data".print();
     data.print();
     app.delay(20000);
   }
   
   handleLoopGct() {
      fields {
        Int count;
      }
      if (undef(count)) { count = 1; }
      if (count >= 10000) {
        count.setValue(5000);
      }
      count++=;
      
     Container:List cl = Container:List.new();
     "after cl cons".print();
     cl += count;
     "after cl add count".print();
     cl += "Hi there bob";
     "after cl add str".print();
     
     cl[0].print();
     cl[1].print();
     
     app.delay(50);
   }
   
}
