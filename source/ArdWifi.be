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

class Embedded:Wifi {

  default() self {
    fields {
      String mode;
      String ssid;
      String password;
      Bool up = false;
      String localIP;
    }
  }

  clear() {
    mode = null;
    up = false;
    localIP = null;
  }

  clearAll() {
    clear();
    ssid = null;
    password = null;
  }

  new(String _ssid, String _password) self {
    ssid = _ssid;
    password = _password;
  }

  macAddressGet() String {
    String macAddress;
    emit(cc) {
      """
      String mac = WiFi.macAddress();
      std::string macs = std::string(mac.c_str());
      beq->bevl_macAddress = new BEC_2_4_6_TextString(macs);
      """
    }
    return(macAddress);
  }

  scanNetworks() List {
    List networks = List.new();
    String network;
    emit(cc) {
      """
      int numberOfNetworks = WiFi.scanNetworks();

      for(int i =0; i<numberOfNetworks; i++){
        String ssid = WiFi.SSID(i);
        std::string ssids = std::string(ssid.c_str());
        beq->bevl_network = new BEC_2_4_6_TextString(ssids);
        beq->bevl_networks->bem_addValue_1(beq->bevl_network);
      }

      """
    }

    return(networks);
  }

  startAp() {
      clear();
      mode = "ap";
      ("Starting AP " + ssid).print();
      emit(cc) {
      """
      boolean result = false;
      if (bevp_password == nullptr) {
        result = WiFi.softAP(bevp_ssid->bems_toCcString().c_str());
      } else {
        result = WiFi.softAP(bevp_ssid->bems_toCcString().c_str(), bevp_password->bems_toCcString().c_str());
      }
      if(result == true)
      {
        //Serial.println("AP Started");
        String lip = WiFi.softAPIP().toString();
        std::string lips = std::string(lip.c_str());
        bevp_localIP = new BEC_2_4_6_TextString(lips);
        bevp_up = BECS_Runtime::boolTrue;
      }
      else
      {
        //Serial.println("AP Start Failed!");
        bevp_up = BECS_Runtime::boolFalse;
      }
      """
      }
    }

  start() {
    clear();
    mode = "station";
    ("Connecting to " + ssid).print();
    emit(cc) {
    """
    WiFi.setAutoReconnect(false);
    WiFi.persistent(false);
    WiFi.begin(bevp_ssid->bems_toCcString().c_str(), bevp_password->bems_toCcString().c_str());
    int count = 0;
    while (WiFi.status() != WL_CONNECTED && count < 40) {
      delay(500);
      Serial.print(".");
      count++;
    }
    if (WiFi.status() == WL_CONNECTED) {
      //Serial.print("Connected, IP address:\t");
      WiFi.setAutoReconnect(false);
      WiFi.persistent(false);
      Serial.println(WiFi.localIP());

      String lip = WiFi.localIP().toString();
      std::string lips = std::string(lip.c_str());
      bevp_localIP = new BEC_2_4_6_TextString(lips);

      bevp_up = BECS_Runtime::boolTrue;
    } else {
      //Serial.println("no luck connecting to wifi");
      bevp_up = BECS_Runtime::boolFalse;
    }
    """
    }
    //("Connected to " + ssid).print();
  }

    isConnectedGet() Bool {
      unless (up && TS.notEmpty(mode) && mode == "station") {
        return(false);
      }
      Bool connected;
      emit(cc) {
      """
      if (WiFi.status() == WL_CONNECTED) {
        //Serial.println("wifi still connected");
        beq->bevl_connected = BECS_Runtime::boolTrue;
      } else {
        //Serial.println("wifi no more connected");
        beq->bevl_connected = BECS_Runtime::boolFalse;
      }
      """
      }
      return(connected)
    }

  stop() {
    clear();
    emit(cc) {
    """
    WiFi.disconnect();
    """
    }
  }

}
