// Copyright 2016 The Brace Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

class Test:TestHelloWorld{
   
   main() {
      emit(js) {
      """
      debugger;

let message = "Hello, world - besample";
trace(message + "\n");
      """
      }
      for (auto i = 1; i < 10;i++=) {
              emit(js) {
              """
              //debugger;

        let message2 = "Hello, world - besample loop";
        trace(message2 + "\n");
              """
              }
        //Time:Sleep.sleepSeconds(1);
      }
   }
   
}

