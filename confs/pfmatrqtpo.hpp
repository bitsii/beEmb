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
//#define BESPEC_SW "1,p2.Generic.22"  //supergeneric
//#define BESPEC_SW "1,p2.WNN.31"  //nodemcu
//#define BESPEC_SW "1,q,p3,p2.Rando.69" //testing changes
#define BESPEC_SW "1,q,nm,a1,t2,p6,p2.rMatrPo.111"  //nodemcu q = quickstate, p2 auth type 2 (hash), p2 always last
//#define BESPEC_SW  "0.DollaTek.20" //dollatek 2mb 1led
//#define BESPEC_SW "1,p2.WNAP2.29" //Athom Plug V2 US THE REAL ONE
// UPD
//#define BE_UPDBASE "na"  //if we don't have one.  otherwise, the url base for the update ver txt file and binfiles
#define BE_UPDBASE "http://storage.googleapis.com/casnicdl.casnic.net/pfmatrqtpo.ino.adafruit_qtpy_esp32"
//
// CON - definition of device's controls
// ctlconfver.control.ctlconf,args.control.ctlconf,args
//
#define BESPEC_CON "" //supergeneric
//
//FOR THE BELOW LINE THIS IS HOW TO SETUP THE BUTTON on a node mcu, follow
//this site roughly https://miliohm.com/arduino-button-without-resistor-pull-up-or-pull-down/
//one of the two wires (on my bboard the green one) goes on GND, the other on D5/GPIO 14, the other
//ends of those wires on each side of the button that closes them when pushed
//
//#define BESPEC_CON "0.sw.2.dim.13.sw.12.sw.14" //motor test, sw is just led to see if powered, 13 enable/speed, 12 input 1 direction 14 input 2 direction (should be one off one on) 13 is to ena of l298n, 12 to in1, 14 to in2
//#define BESPEC_CON "0.pwm.2,1" //nodemcu just pwm local led
//#define BESPEC_CON "0.sw.2,1" //nodemcu just sw. claimed for DOIT ESP32 DEVKIT V1 - WORKS
//#define BESPEC_CON "0.sw.30,2" //trying DevKitC-02 ESP32-C3-WROOM-02 - WORKS
//#define BESPEC_CON "0.sw.2.bu.14,0,30,0,10000" //nodemcu like athsw
//#define BESPEC_CON "0.dim.2,1" //nodemcu just dim local led (reversed)
//#define BESPEC_CON "0.rgbcwgd.4,12,14,5,13" //all in one, pins cold, warm, red, green, blue, gammadim, exclusive cw or rgb
//#define BESPEC_CON "0.rgbcwsgd.4,12,14,5,13" //all in one, pins cold, warm, red, green, blue, gammadim, exclusive cw or rgb. for cw not two pins mixing but one pin for lvl and one for temp
//#define BESPEC_CON "0.rgb.4,12,14" //nodemcu rgb
//#define BESPEC_CON "0.rgbgdim.4,12,14" //nodemcu rgb
//#define BESPEC_CON "0.cwgd.5,13"  //color temp only 2 leds, 5 cold, 13 warm
//#define BESPEC_CON "0.cwgd.14,4" //red warm, blue cold  first pin cold, second warm
//#define BESPEC_CON "0.gdim.5.gdim.13" //
//#define BESPEC_CON "0.rgb.4,12,14.str.0" //nodemcu rgb strobe
//
//#define BESPEC_CON "0.sw.16"  //dollatek - one sw on 16
//#define BESPEC_CON "0.dim.16"  //dollatek - one dim on 16
//#define BESPEC_CON "0.sw.12,1.bu.5,0,30,0,30000"  //12 is switch, 13 is led, 5 button - athom plug v2 us - esp8266ex 2mb THE REAL ONE sic look unnecessary led does on it's own
//#define BESPEC_CON "0.sw.12,1" //Athom Plug V2 US - sw on 12, 13 is led, default - same for martin jerry
//#define BESPEC_CON "0.sw.12.sw.13"  //12 is switch, 13 is led - athom plug v2 us - esp8266ex 2mb
//#define BESPEC_CON "0.sw.2.bu.5,0,0,0,0" //nodemcu like athsw
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
