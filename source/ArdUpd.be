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
      //Int upCheckIv = 20000;//millis per each check, 43200000 is 12 hours, 86400000 one day
      Int upCheckIv = 43200000;//millis per each check, 43200000 is 12 hours, 86400000 one day
      Int nextUpCheck = ash.nowup + upCheckIv;
      String updBase;
    }
    emit(cc) {
      """
      std::string updBase = BE_UPDBASE;
      bevp_updBase = new BEC_2_4_6_TextString(updBase);
      """
    }
    if (TS.isEmpty(updBase) || updBase == "na") {
      updBase = "";
    }
  }

  handleLoop() {
    if (ash.nowup > nextUpCheck) {
      nextUpCheck = ash.nowup + upCheckIv;
      handleUpdate();
    }
  }

  handleUpdate() {
    String verGetRes;
    if (TS.notEmpty(updBase)) {
      String ver = ash.swSpec.split(".").last;
      //("str ver is " + ver).print();
      String updVf = updBase + "." + ver + ".txt";
      ("updVf " + updVf).print();
      emit(cc) {
        """
#ifdef BEAR_ESP8266
WiFiClient client;
HTTPClient http;
http.begin(client, beq->bevl_updVf->bems_toCcString().c_str());
#endif
#ifdef BEAR_ESP32
  HTTPClient http;
  http.begin(beq->bevl_updVf->bems_toCcString().c_str());
#endif
  int httpCode = http.GET();
  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      if (payload.length() > 0) {
        Serial.println(payload);
        std::string lips = std::string(payload.c_str());
        beq->bevl_verGetRes = new BEC_2_4_6_TextString(lips);
      }
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
        """
      }
      if (TS.notEmpty(verGetRes)) {
        ("verGetRes " + verGetRes).print();
        var vgl = verGetRes.split(":");
        //("vgl len " + vgl.length).print();
        if (vgl.length > 2) {
          String nvs = vgl[1];
          //("nvs " + nvs).print();
          Int nvi = Int.new(nvs);
          //Int veri = Int.new(ver);
          String updUrl = updBase + "." + nvs + ".bin";
          ifEmit(bearEsp8266) {
            updUrl += ".gz";
          }
          ("updUrl " + updUrl).print();
          updateFromUrl(updUrl);
        }
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
