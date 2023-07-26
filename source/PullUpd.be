// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;

class Embedded:PullUpdate {

     emit(cc_classHead) {
   """

   """
     }

     new(List cmdl) {
       fields {
         String sourceIp;
         Int sourcePort;
         Int sourceSize;
       }
       if (cmdl.size < 5) {
         "PullUpd new cmdl missing items".print();
         return(self);
       }
       try {
        sourceIp = cmdl[2];
        sourcePort = Int.new(cmdl[3]);
        sourceSize = Int.new(cmdl[4]);
       } catch (any e) {
        "PullUpd new failed".print();
       }
       return(self);
     }

     start() String {
       if (undef(sourceSize) || undef(sourcePort) || TS.isEmpty(sourceIp)) {
         auto msg = "sourceSize, sourcePort, or sourceIp missing";
         msg.print();
         return(msg);
       }
       Bool ok = false;
       String err;
       emit(cc) {
         """
         //440377
         if (Update.begin(bevp_sourceSize->bevi_int)) {
           beq->bevl_ok = BECS_Runtime::boolTrue;
         } else {
           StreamString errss;
           Update.printError(errss);
           std::string errs = std::string(errss.c_str());
           beq->bevl_err = new BEC_2_4_6_TextString(errs);
         }
         """
       }
       if (ok) {
        msg = "Update started ok";
       } else {
        msg = "Update failed to start " + err;
       }
       msg.print();
       return(msg);
     }

     handleUpdate() {

     }

}
