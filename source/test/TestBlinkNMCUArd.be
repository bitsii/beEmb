// Copyright 2016 The Brace Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Math:Int;

class Test:TestBlink{
   
   main() {
      //"Content-type: text/html\n\n<html><body>Hello there</body></html>".print();
      testGc();
      emit(cc) {
      """
      delay(1000);
  digitalWrite(2,HIGH);
  delay(3000);
  digitalWrite(2,LOW);
      """
      }
      "Hello Arduino from Be".print();
      
   }
   
   testGc() {
      "In testGc()".print();
      for (Int i = 0;i < 1;i = i++) {
         for (Int j = 0;j < 50000;j = j++) { //normally 50000 did 5000000 to stress with threads
            Int k = Int.new();
         }
      }
      "testGc() Done".print();
   }
}

