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
#define BESPEC_SW "1,q,p3,p2.rAthBlb15w.56"  //generic configurable controls Athlb017w LB01-7W-B22
//
// CON - definition of device's controls
// ctlconfver.control.ctlconf,args.control.ctlconf,args
//
//#define BESPEC_CON "" //supergeneric
//Just the R G B part now
//FOR THE LB01-15W 4,5,12,13i,14 looks like 4,12,14 are r,g,b 5 is white level 13 is temp
//#define BESPEC_CON "0.rgb.4,12,14"
//#define BESPEC_CON "0.rgbgdim.4,12,14"
#define BESPEC_CON "0.rgbcwsgd.4,12,14,5,13"
//putconfigs pass raw fc.conspec 0.dim.2,0 e
//
//pinposes //16, 2 nodemcu - Athom 16A US 13 LED 14 RELAY, SONOFF BASIC R2 13 LED 12 RELAY, 16 for dollatek 8285
//
// Is Reset by Pin supported - when not on network can use pin to reset device (clear all config, prep for
// re-setup).  For most (and secure) devices a physical option (button) is instead recommended, but for
// things like bulbs/less sensitive devices w/out another reasonable choice, it should be enabled.  device
// waits a bit for the wifi to come up when configured  to avoid power losses leading to entering this mode
//
#define BE_RESETBYPOW "on" //enabled
//#define BE_RESETBYPOW "off" //disabled
//
// tcpconsole - if you want to enable a debugish tcp port on the device (all be prints will be echoed there)
// turn BE_TCPCONSOLE on, otherwise leave off.  only for development, really only useful if serial connection
// not available.  You can telnet to the device's ip port 32259 to see the messages.  output only, no input
//
//#define BE_TCPCONSOLE "on" //enabled
#define BE_TCPCONSOLE "off" //disabled
//
//
// aptype - one of I included, U unincluded, O open, for wifi sec
// the controls how the Access Point for (re) provisioning behaves
// if set to O it is open and the setup code / pin is in the name (default, but for highly trusted environments and development only)
// if set to I it is included and the setup code / pin is still in the name (again, trusted environments as the pin is given, but
// the passwords during setup will be protected by WPA)
// if set to U (recommended, but less convenient) the 8 digit setup code / pin must be provided separately, it is not available in the ap name / from the device during setup
//
#define BE_APTYPE "O"
//#define BE_APTYPE "S"
//
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
