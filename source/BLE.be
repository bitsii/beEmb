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
BLEServer* pServer = NULL;
BLECharacteristic* pTxCharacteristic;
static bool deviceConnected;
static bool oldDeviceConnected;
static uint8_t txValue;
"""
}

emit(cc) {
"""
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"  // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    BEC_2_8_3_EmbeddedBLE::deviceConnected = true;
    Serial.println("Device connected");
  };

  void onDisconnect(BLEServer *pServer) {
    BEC_2_8_3_EmbeddedBLE::deviceConnected = false;
    Serial.println("Device disconnected");
  }
};

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String rxValue = pCharacteristic->getValue();

    if (rxValue.length() > 0) {
      Serial.println("*********");
      Serial.print("Received Value: ");
      for (int i = 0; i < rxValue.length(); i++) {
        Serial.print(rxValue[i]);
      }

      Serial.println();
      Serial.println("*********");
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
    BEC_2_8_3_EmbeddedBLE::deviceConnected = false;
    BEC_2_8_3_EmbeddedBLE::oldDeviceConnected = false;

    // Create the BLE Device
    BLEDevice::init("UART Service");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pTxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);

    // Descriptor 2902 is not required when using NimBLE as it is automatically added based on the characteristic properties
    pTxCharacteristic->addDescriptor(new BLE2902());

    BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);

    pRxCharacteristic->setCallbacks(new MyCallbacks());

    // Start the service
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();
    Serial.println("Waiting a client connection to notify...");
    """
    }
  }
  
  write(String line) self {
    emit(cc) {
    """
    //Serial.write(beq->beva_line->bems_toCcString().c_str());
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
