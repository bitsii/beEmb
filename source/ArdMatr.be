/*
 * Copyright (c) 2024-2025, the Beysant Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:AppShell;
use Embedded:Config;

//
//https://github.com/espressif/arduino-esp32/blob/master/libraries/Matter/examples/MatterOnOffLight/MatterOnOffLight.ino
//put in BEAR_Imports.hpp for esp32
//#include <Matter.h>
//
//looks like max 15 devices/endpoints supported at present

use Embedded:CommonNames as CNS;

emit(cc) {
  """
  //have mutex, deque for positions, deque for bools, lock before changing or iterating for changes
  bool setLightOnOff(size_t idx, bool state) {
    Serial.printf("Light %zu changed state to: %d\r\n", idx, state);
    return true;
  }
  bool sloo0(bool state) { return setLightOnOff(0, state); }
  bool sloo1(bool state) { return setLightOnOff(1, state); }
  """
}

class Embedded:MatrServer {

emit(cc_classHead) {
"""
std::vector<std::shared_ptr<MatterOnOffLight>> bevi_mools;
"""
}

  new(_ash) self {
    slots {
      Embedded:AppShell ash = _ash;
    }
  }

  start() {
    emit(cc) {
      """
      std::shared_ptr<MatterOnOffLight> bevi_mool;

      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo0);
      bevi_mools.push_back(bevi_mool);

      bevi_mool = std::make_shared<MatterOnOffLight>();
      bevi_mool->begin();
      bevi_mool->onChangeOnOff(sloo1);
      bevi_mools.push_back(bevi_mool);

      Matter.begin();
      """
    }
  }

  checkGetCommission() {
    emit(cc) {
      """
      //Matter.decommission();
      if (!Matter.isDeviceCommissioned()) {
        Serial.println("");
        Serial.println("Matter Node is not commissioned yet.");
        Serial.println("Initiate the device discovery in your Matter environment.");
        Serial.println("Commission it to your Matter hub with the manual pairing code or QR code");
        Serial.printf("Manual pairing code: %s\r\n", Matter.getManualPairingCode().c_str());
        Serial.printf("QR code URL: %s\r\n", Matter.getOnboardingQRCodeUrl().c_str());
        // waits for Matter Light Commissioning.
        uint32_t timeCount = 0;
        while (!Matter.isDeviceCommissioned()) {
          delay(100);
          if ((timeCount++ % 50) == 0) {  // 50*100ms = 5 sec
            Serial.println("Matter Node not commissioned yet. Waiting for commissioning.");
          }
        }
        Serial.println("Matter Node is commissioned and connected to Wi-Fi. Ready for use.");
      } else {
        //Serial.println("Matter Node already provisioned");
        //int n = MDNS.queryService("http", "tcp");
        //Serial.printf("Found %d services:\n", n);
      }
      """
    }
  }

  decommission() {
    emit(cc) {
      """
      Matter.decommission();
      """
    }
  }

}
