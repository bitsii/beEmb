#define BEDCC_SGC
#define BEDCC_NORTTI
#define BEAR_ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266httpUpdate.h>
#include <EEPROM.h>
#include <Hash.h>
//for CDS.be multicast udp
#include <WiFiUdp.h>
#define MQTT_DEBUG
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
