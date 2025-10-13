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

class Embedded:Update {

  new(_ash) self {
    slots {
      Embedded:AppShell ash = _ash;
    }
    fields {
      String supurl;
      Int nextUfuCheck = ash.nowup + 60000;
    }
  }

  handleLoop() {
    Int nowup = ash.nowup;
    if (nowup > nextUfuCheck) {
      nextUfuCheck = nowup + 60000;
      if (def(supurl) && TS.notEmpty(supurl)) {
        String upurl = supurl;
        supurl = null;
        updateFromUrl(upurl);
      }
    }
  }

  updateFromUrl(String url) {

    Int res = Int.new();
    emit(cc) {
     """
     Serial.println("gonna update");
     Serial.println("SketchSize and FreeSketchSpace");
     Serial.println(ESP.getSketchSize());
     Serial.println(ESP.getFreeSketchSpace());
#ifdef BEAR_ESP8266
     WiFiClient client;
     t_httpUpdate_return ret = ESPhttpUpdate.update(client, beq->beva_url->bems_toCcString().c_str());
     Serial.println(ESPhttpUpdate.getLastError());
     Serial.println(ESPhttpUpdate.getLastErrorString());
#endif
#ifdef BEAR_ESP32
     NetworkClient client;
     t_httpUpdate_return ret = httpUpdate.update(client, beq->beva_url->bems_toCcString().c_str());
     Serial.println(httpUpdate.getLastError());
     Serial.println(httpUpdate.getLastErrorString());
#endif
     """
    }

  }

}
