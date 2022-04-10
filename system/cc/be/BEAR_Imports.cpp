#include <Arduino.h>
#include <bearssl/bearssl.h>
#include "lwip/udp.h"
#include "lwip/igmp.h"
#define SSDP_MULTICAST_ADDR 239, 255, 255, 250
#define SSDP_PORT         1989
