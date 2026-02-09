// CONFIGURATION OPTIONS HERE
// pick one set of BESPEC_SW and BESPEC_CON to correspond to your device
// and configtype/pin use
// ard/BEH_4_Base.hpp secion is regenerated from system/cc/be/BEAR_Conf.hpp during bebuild, so
// keep this section in sync between both files
// BESPEC_SW and BESPEC_CON can also be overridden on the device later
// via commands (suggest starting with "supergeneric" options below)
//
// SW - name (type) and version of the device.  Typename 10 char max ssid rules (no spaces)
// swconfver.DeviceTypeName.DeviceVersion
//
#define BESPEC_SW "1,q,df,p6,p2.Plug.135" //template plug df,
// Esp32 4mb minimal spiffs 1.9mb app with ota/190kb spiffs  esp32c3
// CON - definition of device's controls
// ctlconfver.control.ctlconf,args.control.ctlconf,args
//
//#define BESPEC_CON "" //supergeneric
//#define BESPEC_CON "0.sw.30,2" //trying DevKitC-02 ESP32-C3-WROOM-02 - WORKS (NEOPIXEL GPIO 8 + 22 SOC GPIO)
#define BESPEC_CON "0.sw.39,2" //trying NanoESP32-C6 ESP32-C6-WROOM-1 - WORKS (NEOPIXEL GPIO 8 + 31 SOC GPIO)
//#define BESPEC_CON "0.sw.5,1" //just the relay first
//#define BESPEC_CON "0.sw.5,1.bu.3,0,30,0,30000"  //5 is switch, 6 is led, 3 button
//
// Is Reset by power on off supported
// https://gitlab.com/bitsii/CasCon/-/wikis/Advanced-Topics#resetting-a-device
//
#define BE_RESETBYPOW "on" //enabled
//
// tcpconsole - if you want to enable a debugish tcp port on the device (all be prints will be echoed there)
// turn BE_TCPCONSOLE on, otherwise leave off.  only for development, really only useful if serial connection
// not available.  You can telnet to the device's ip port 32259 to see the messages.  output only, no input
//
#define BE_TCPCONSOLE "off"
//
//
#define BE_APTYPE "O"
//
// Setup Code - if set to 8 character string of lower case letters this will be used as your setup code instead of
// a randomly generated one.  This can be especially useful for a BE_HIDECODE of "on" so you don't have to search the
// console for it / so you can do headless setup if you are putting on a sealed device OTA.
//
#define BE_SCODE "na" //a non-empty value should be set, set to < 8 chars to ignore/generate random
//#define BE_SCODE "abcdefgh" //right length for use, set to 8 char lower case letters
//
//
//Hide the setup code - requireing the setup user to be given the setup code in some other way (packaging, etc)
//great for more secure setup, code is not in the ssid and must be entered during setup.  little less convenient.
//on to hide code, off to not hide code (show it in ssid, app will auto-populate it)
//
#define BE_HIDECODE "off"
//#define BE_HIDECODE "on"
//
// END OF CONFIGURATION OPTIONS
//
//for BLE.be
#include <NimBLEDevice.h>
