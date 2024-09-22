#define BEDCC_NORTTI
#ifdef BEAR_ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266httpUpdate.h>
#include <Hash.h>
#endif
#ifdef BEAR_ESP32
#include <WiFi.h>
#include <ESPmDNS.h>
#include "SPIFFS.h"
#include <SimpleHOTP.h>
#endif
//#include <EEPROM.h>
#include <FS.h>
//#include <LittleFS.h>
