#include <Arduino.h>
#define BEAR_ESP8266
//#include <bearssl/bearssl.h>
//for CDS.be multicast udp
#include "lwip/udp.h"
#include "lwip/igmp.h"
#define SSDP_MULTICAST_ADDR 239, 255, 255, 250
#define SSDP_PORT         3200
