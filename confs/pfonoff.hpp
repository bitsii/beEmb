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
#define BESPEC_SW "1,q,p6,p2.OnOff.133"
//
// CON - definition of device's controls
// ctlconfver.control.ctlconf,args.control.ctlconf,args
//
#define BESPEC_CON "0.sw.2" //simple nodemcu for majority with LED on gpio 2, if your board is different change the "2" to your boards built in LED pin.
//#define BESPEC_CON "0.sw.12,1.bu.5,0,30,0,9000"  //12 is switch, 13 is led, 5 button resets if button held down for 9secs+
//#define BESPEC_CON "0.sw.8" //DevKitC-02 ESP32-C3-WROOM-02
//#define BESPEC_CON "0.sw.2.bu.14,0,30,0,10000" //nodemcu
//#define BESPEC_CON "0.sw.12,1" //
//#define BESPEC_CON "0.sw.12.sw.13"  //12 is switch, 13 is led
//#define BESPEC_CON "0.sw.2.bu.5,0,0,0,0" //
//
// Is Reset by power on off supported
// https://gitlab.com/bitsii/CasCon/-/wikis/Advanced-Topics#resetting-a-device
//
#define BE_RESETBYPOW "off" //if you don't have a physical button for reset, this should be "on"
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
