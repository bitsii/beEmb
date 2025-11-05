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
#define BESPEC_SW "1,q,p6,p2.rIotBlb12Df.172"  //template for rgb cold warm bulb df,
//
#define BESPEC_CON "0.rgbcwgd.6,7,5,3,4" //all in one, red, green, blue, (cold) white, (warm) white
//
// Is Reset by power on off supported
// https://gitlab.com/bitsii/CasCon/-/wikis/Advanced-Topics#resetting-a-device
//
#define BE_RESETBYPOW "on" //enabled
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
