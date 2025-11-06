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
    HTTPClient http;

    const uint32_t ACTIVE_SKETCH_ADDRESS = 0x10000;
    const uint32_t SECTOR_SIZE_BYTES = 4096; // Renamed to avoid conflict with system macro

    // Begin HTTP connection
    http.begin(client, beq->beva_url->bems_toCcString().c_str());
    int httpCode = http.GET();

    if (httpCode != HTTP_CODE_OK) {
        Serial.printf("HTTP failed, error: %s\n", http.errorToString(httpCode).c_str());
        http.end();
        return nullptr;
    }

    size_t contentLen = http.getSize();
    Serial.printf("Received content length: %u bytes\n", contentLen);

    if (contentLen <= 0) {
        Serial.println("Error: Content length is zero or invalid.");
        http.end();
        return nullptr;
    }

    // --- Direct Flash Write ---

    WiFiClient* stream = http.getStreamPtr();
    uint32_t currentFlashAddress = ACTIVE_SKETCH_ADDRESS;
    uint32_t endFlashAddress = ACTIVE_SKETCH_ADDRESS + contentLen;
    uint32_t bytesWritten = 0;
    uint8_t writeBuffer[512];

    // 2. WRITE BINARY CHUNKS
    while (bytesWritten < contentLen) {
        size_t bytesToRead = min(sizeof(writeBuffer), contentLen - bytesWritten);
        size_t bytesRead = stream->readBytes(writeBuffer, bytesToRead);

        if (bytesRead > 0) {
            if (!ESP.flashWrite(currentFlashAddress, (uint32_t*)writeBuffer, bytesRead)) {
                 Serial.printf("Fatal Error: Failed to write to 0x%X\n", currentFlashAddress);
                 http.end();
                 return nullptr;
            }

            currentFlashAddress += bytesRead;
            bytesWritten += bytesRead;
            //Serial.printf("Progress: %u%%\r", (bytesWritten * 100) / contentLen);
        } else if (bytesRead == 0 && bytesWritten < contentLen) {
            //Serial.println("\nError: Stream unexpectedly ended.");
            break;
        }
    }

    http.end();
    Serial.println("\nFlash write complete.");

    if (bytesWritten == contentLen) {
        Serial.println("Rebooting now.");
        ESP.restart();
    } else {
        Serial.println("Flash write failed or size mismatch. Device likely corrupted.");
    }
    return nullptr;

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
