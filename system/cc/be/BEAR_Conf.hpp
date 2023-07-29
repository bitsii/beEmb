// CONFIGURATION OPTIONS HERE
// pick one set of BESPEC_SW and BESPEC_CON to correspond to your device
// and configtype/pin use
// ard/BEH_4_Base.hpp secion is regenerated from system/cc/be/BEAR_Conf.hpp during bebuild, so
// keep this section in sync between both files
// BESPEC_SW and BESPEC_CON can also be overridden on the device later
// via commands (suggest starting with "supergeneric" options below)
//
// SW - name (type) and version of the device
// swconfver.DeviceTypeName.DeviceVersion
//
//#define BESPEC_SW "0.Generic.22"  //supergeneric
//#define BESPEC_SW "0.NodeMcuLeds.24"  //nodemcu
//#define BESPEC_SW  "0.DollaLed.20" //dollatek 2mb 1led
//#define BESPEC_SW "0.AthomPlugV2.26" //Athom Plug V2 US
#define BESPEC_SW "0.NodeAthswy.25"  //nodemcu like athsw
//
// CON - definition of device's controls
// ctlconfver.control.ctlconf,args.control.ctlconf,args
//
//#define BESPEC_CON "" //supergeneric
//#define BESPEC_CON "0.sw.16.dim.2" //nodemcu
//#define BESPEC_CON "0.sw.16"  //dollatek - one sw on 16
//#define BESPEC_CON "0.dim.16"  //dollatek - one dim on 16
//#define BESPEC_CON "0.sw.12,1" //Athom Plug V2 US - sw on 12, 13 is led, default - same for martin jerry
//#define BESPEC_CON "0.sw.12.sw.13"  //12 is switch, 13 is led - athom plug v2 us - esp8266ex 2mb
#define BESPEC_CON "0.sw.2.bu.5.sic.16,0,0" //nodemcu like athsw
//
//pinposes //16, 2 nodemcu - Athom 16A US 13 LED 14 RELAY, SONOFF BASIC R2 13 LED 12 RELAY, 16 for dollatek 8285
//
// END OF CONFIGURATION OPTIONS
//
