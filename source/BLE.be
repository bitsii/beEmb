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


emit(cc) {
"""
#define SERVICE_UUID        "6cbe56f2-1858-4ca7-87b3-618ae26a12d6"
#define CMD_UUID "6cbe56f2-2858-4ca7-87b3-618ae26a12d6"
#define RES_UUID "6cbe56f2-3858-4ca7-87b3-618ae26a12d6"

int32_t lastCm = 0;
int32_t nowCm = 0;
String nowCs;
BLECharacteristic *pCharacteristicR;

class MyCallbacksC : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic *pCharacteristic, NimBLEConnInfo& connInfo) {
    String value = pCharacteristic->getValue();

    if (value.length() > 0) {
      nowCs = value;
      nowCm = millis();

      /*Serial.println("*********");
      Serial.print("C New value: ");
      for (int i = 0; i < value.length(); i++) {
        Serial.print(value[i]);
      }

      Serial.println();
      Serial.println("*********");*/
    }
  }
};

class ServerCallbacks : public NimBLEServerCallbacks {

    void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) override {
        Serial.printf("Client disconnected - start advertising\n");
        NimBLEDevice::startAdvertising();
    }

} serverCallbacks;
"""
}
  
  new(String _finssidp) self {
    slots {
      String finssidp = _finssidp;
    }
  }

  default() self { }
  
  start() {
    "starting bleSup".print();
    emit(cc) {
    """
  NimBLEDevice::init(bevp_finssidp->bems_toCcString().c_str());
  NimBLEServer *pServer = NimBLEDevice::createServer();
  pServer->setCallbacks(&serverCallbacks);

  NimBLEService *pService = pServer->createService(SERVICE_UUID);

  NimBLECharacteristic *pCharacteristicC =
    pService->createCharacteristic(CMD_UUID, NIMBLE_PROPERTY::WRITE);
  pCharacteristicC->setCallbacks(new MyCallbacksC());
  pCharacteristicC->setValue("undefined");

  pCharacteristicR =
    pService->createCharacteristic(RES_UUID, NIMBLE_PROPERTY::READ);
  pCharacteristicR->setValue("undefined");

  pService->start();

  NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->setName(bevp_finssidp->bems_toCcString().c_str());
  pAdvertising->addServiceUUID(pService->getUUID());
  /**
    *  If your device is battery powered you may consider setting scan response
    *  to false as it will extend battery life at the expense of less data sent.
    */
  pAdvertising->enableScanResponse(true);

  pAdvertising->start();
    """
    }
  }
  
  write(String line) self {
    emit(cc) {
    """
    pCharacteristicR->setValue(beq->beva_line->bems_toCcString().c_str());
    """
    }
  }
  
  checkGetPayload(String payload, String endmark) String {
    payload.clear();
    String ncs;
    emit(cc) {
      """
      if (nowCm != lastCm) {
        lastCm = nowCm;
        if (nowCs.length() > 0) {
          std::string ncs = std::string(nowCs.c_str());
          beq->bevl_ncs = new BEC_2_4_6_TextString(ncs);
        }
      }
      """
    }
    if (TS.notEmpty(ncs)) {
      ("ncs " + ncs).print();
      payload += ncs;
    }
    return(payload);
  }
  
  availableGet() Bool {
    return(false);
  }  


  
}
