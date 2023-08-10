/*
 * Copyright (c) 2021-2023, the Bennt Embed Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Text:Strings as TS;
use System:Exception;

class Embedded:App {
   
   default() self { 
     fields {
       any plugin;
       Int hlCount = 0;
       Int zero = 0;
     }
   }
   
   handleWeb(request) {
     //"in app handleweb".print();
     plugin.handleWeb(request);
   }

   startLoop() {
     "IN STARTLOOP".print();
     plugin.startLoop();
     "FINISHING STARTLOOP".print();
   }
   
   handleLoop() {
     if (hlCount > zero) {
       "HLCOUNT ELEVATED".print();
     }
     hlCount++=;
     plugin.handleLoop();
     hlCount--=;
   }
   
   delay(Int millis) {
     emit(cc) {
      """
      delay(beq->beva_millis->bevi_int);
      """
     }
   }

   wdtFeed() {
     emit(cc) {
      """
#ifdef BEAR_ESP8266
      ESP.wdtFeed();
#endif
      """
     }
   }

   wdtDisable() {
     emit(cc) {
      """
#ifdef BEAR_ESP8266
      ESP.wdtDisable();
      //*((volatile uint32_t*) 0x60000900) &= ~(1); // Hardware WDT OFF
#endif
      """
     }
   }

   wdtEnable(Int timeout) {
     emit(cc) {
      """
      //*((volatile uint32_t*) 0x60000900) |= 1; // Hardware WDT ON
      ESP.wdtEnable(beq->beva_timeout->bevi_int);
      """
     }
   }

   yield() {
     emit(cc) {
      """
      yield();
      """
     }
   }
   
   uptime() Int {
     Int millis = Int.new();
     emit(cc) {
     """
     beq->bevl_millis->bevi_int = millis();
     """
     }
     return(millis);
   }
   
   uptime(Int millis) Int {
     emit(cc) {
     """
     beq->beva_millis->bevi_int = millis();
     """
     }
     return(millis);
   }
   
   pinModeOutput(Int pin) {
     emit(cc) {
     """
     //pinMode(255, OUTPUT);
     //analogWrite(255, 0);
     //analogWrite(255, 10);
     pinMode(beq->beva_pin->bevi_int,OUTPUT);
     """
     }
   }

   analogWrite(Int pin, Int value) {
     emit(cc) {
     """
     uint8_t pin = (uint8_t) beq->beva_pin->bevi_int;
     uint8_t value = (uint8_t) beq->beva_value->bevi_int;
     analogWrite(pin,value);
     """
     }
   }

   pinModeInputPullup(Int pin) {
     emit(cc) {
     """
     pinMode(beq->beva_pin->bevi_int,INPUT_PULLUP);
     """
     }
   }
   
   analogRead(Int pin, Int value) Int {
     emit(cc) {
     """
     uint8_t pin = (uint8_t) beq->beva_pin->bevi_int;
     uint8_t value = analogRead(pin);
     beq->beva_value->bevi_int = (int32_t) value;
     """
     }
     return(value);
   }
   
   restart() {
     emit(cc) {
     """
     ESP.restart();
     """
     }
   }

   strToInt(String str) Int {
     //the existing one is "too much"
     Int res = Int.new();
     emit(cc) {
       """
       beq->bevl_res->bevi_int = atoi(beq->beva_str->bems_toCcString().c_str());
       """
     }
     return(res);
   }

   intToStr(Int int) String {
     //the existing one is "too much"
     //THIS IS NOT RELIABLE FOR SOME REASON
     String res;
     emit(cc) {
       """
       char buffer[20];
       itoa(beq->beva_int->bevi_int,buffer,10);
       std::string ints = std::string(buffer);
       beq->bevl_res = new BEC_2_4_6_TextString(ints);
       """
     }
     return(res);
   }

   maybeGc() {
   emit(cc) {
   """
   BECS_Runtime::doGc();
   """
   }
   }

}
