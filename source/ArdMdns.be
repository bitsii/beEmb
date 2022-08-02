// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;

class Embedded:Mdns {

  new(String _name) self {
    fields {
      String name = _name;
    }
  }
  
  start() self {
    if (TS.isEmpty(name)) {
      "mdns needs a name".print();
      return(self);
    }
    emit(cc) {
    """
    int tries = 100;
    if (!MDNS.begin(bevp_name->bems_toCcString().c_str())) {
      Serial.println("Error setting up MDNS responder!");
      while (tries-- > 0) { delay(1000); }
    }
    Serial.println("mDNS responder started");
    """
    }
    return(self);
  }
  
  update() self {
  emit(cc) {
  """
  MDNS.update();
  """
  }
  }
  
}