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
use Encode:Url as EU;

class Embedded:BLE {

emit(cc_classHead) {
"""
"""
}

emit(cc) {
"""
#define SERVICE_UUID                  "4FAFC201-1FB5-459E-8FCC-C5C9C331914B"
#define CHARACTERISTIC_OTA_UUID       "62ec0272-3ec5-11eb-b378-0242ac130005"
class otaCallback: public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
      static esp_ota_handle_t otaHandler = 0;
static const esp_partition_t *update_partition = NULL;

bool downloadFlag = false;
      std::string rxData = pCharacteristic->getValue().c_str();
      if (!downloadFlag) { //If it's the first packet of OTA since bootup, begin OTA
        Serial.println("BeginOTA");
        const esp_partition_t *configured = esp_ota_get_boot_partition();
        const esp_partition_t *running = esp_ota_get_running_partition();

        if (configured != running)
        {
          Serial.printf("Configured OTA boot partition at offset 0x%08x, but running from offset 0x%08x", configured->address, running->address);
          Serial.println("(This can happen if either the OTA boot data or preferred boot image become corrupted somehow.)");
          //TODO: Tell client to abort OTA and why?
          //TODO: Recover...
          esp_ota_end(otaHandler);
        } else {
          Serial.printf("Running partition type %d subtype %d (offset 0x%08x) ", running->type, running->subtype, running->address);
        }

        update_partition = esp_ota_get_next_update_partition(NULL);
        assert(update_partition != NULL);

        Serial.printf(" Writing to partition subtype %d at offset 0x%x", update_partition->subtype, update_partition->address);

        esp_ota_begin(update_partition, OTA_SIZE_UNKNOWN, &otaHandler);
        //OTA Add error handling if ota begin fails
        downloadFlag = true;
      }
      if (rxData.length() > 0) //
      {
        if(esp_ota_write(otaHandler, rxData.c_str(), rxData.length()) != ESP_OK) {
          Serial.println("Error: write to flash failed");
        }

        if (rxData.length() < 512) // TODO Asumes at least 512 data bytes (@BLE 4.2). Change to: set via message from client
        {
          //Final chunk arrived
          if (esp_ota_end(otaHandler) != ESP_OK)
          {
            Serial.println("OTA end failed ");
            //TODO Deal with error. Tell client about it
            return;
          }
          Serial.println("Set Boot partion");
          if (ESP_OK == esp_ota_set_boot_partition(update_partition))
          {
            esp_ota_end(otaHandler);
            Serial.println("Wait 1 sec...");
            delay(1000);
            downloadFlag = false;
            Serial.println("Restarting...");
            esp_restart();
            return;
          }
          else
          {
            Serial.println("Upload Error");
            downloadFlag = false;
            //TODO Deal with error. Tell client about it
            esp_ota_end(otaHandler);
            return;
          }
        }
      } else {
        downloadFlag = false;
      }
    }
};
"""
}
  
  new() self {
  }
  
  start() {
    emit(cc) {
    """
BLEServer* pServer = NULL;
BLECharacteristic * pOtaCharacteristic;
  // 1. Create the BLE Device
  BLEDevice::init("ESP32 iOS OTA");
  BLEDevice::setMTU(517);
  nvs_flash_erase(); //TODO evaulate the need for this
  BLEDevice::setMTU(517);

  // 2. Create the BLE server
  pServer = BLEDevice::createServer();
  //pServer->setCallbacks(new MyServerCallbacks());

  // 3. Create BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // 4. Create BLE Characteristics inside the service(s)
  pOtaCharacteristic = pService->createCharacteristic(CHARACTERISTIC_OTA_UUID,
                       BLECharacteristic::PROPERTY_WRITE_NR);
  pOtaCharacteristic->setCallbacks(new otaCallback());

  // 5. Start the service(s)
  pService->start();
    """
    }
  }
  
  write(String line) self {
    emit(cc) {
    """
    """
    }
  }
  
  checkGetPayload(String payload, String endmark) String {
    payload.clear();
    return(payload);
  }
  
  availableGet() Bool {
    return(false);
  }  
  
}
