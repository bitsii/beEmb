//
// DYNCONF dynConf, options set by configuration, not here.  docs are here tho, see below
//
// over serial or network after initial setup, set the values via putconfigs (can do > 1 at once, to some limit)
// like so
// putconfigs pass raw fc.conspec 0.dim.2 e
//
// configs in pairs, extra item at the end. can be raw or hex encoded, raw tends to be fine.  specific value and meaning below
//
// SW - name (type) and version of the device.  Typename 10 char max ssid rules (no spaces)
// swconfver.DeviceTypeName.DeviceVersion
//
// if unset is 1,q,p3,p2.Unspeced.5 (ish)
// putconfigs pass raw fc.swspec 1,q,p3,p2.rNodeMCU.68 e
//
// CON - definition of device's controls
// ctlconfver.control.ctlconf,args.control.ctlconf,args
//
// if unset is empty
// putconfigs pass raw fc.conspec 0.gdim.2,1 e
//
// pinposes //16, 2 nodemcu - Athom 16A US 13 LED 14 RELAY, SONOFF BASIC R2 13 LED 12 RELAY, 16 for dollatek 8285
//
// Is Reset by Pin supported - when not on network can use pin to reset device (clear all config, prep for
// re-setup).  For most (and secure) devices a physical option (button) is instead recommended, but for
// things like bulbs/less sensitive devices w/out another reasonable choice, it should be enabled.  device
// waits a bit for the wifi to come up when configured  to avoid power losses leading to entering this mode
//
// on or off, if unset is on
// putconfigs pass raw fc.rbps off e
//
// tcpconsole - if you want to enable a debugish tcp port on the device (all be prints will be echoed there)
// turn tccon on, otherwise leave off.  only for development, really only useful if serial connection
// not available.  You can telnet to the device's ip port 32259 to see the messages.  output only, no input
//
// on or off, if unset is off
// putconfigs pass raw fc.tccon on e
//
//
// aptype - one of O open or S secured for wifi sec
// this controls how the Access Point for (re) provisioning behaves
// if set to O it is open and there's no password for the setup access point
// if set to S it is secured and a password is required for the setup access point (WEP)
//
// O or S. if unset is O
// putconfigs pass raw fc.apType S e
//
// Setup Code - if set to 8 character string of lower case letters this will be used as your setup code instead of
// a randomly generated one.  This can be especially useful for a fc.hideCode of on so you don't have to search the
// console for it / so you can do headless setup if you are putting on a sealed device OTA.
//
// if unset a random one is generated
// putconfigs pass raw fc.scode abcdefgh e
//
//Hide the setup code - requireing the setup user to be given the setup code in some other way (packaging, etc)
//great for more secure setup, code is not in the ssid and must be entered during setup.  little less convenient.
//on to hide code, off to not hide code (show it in ssid, app will auto-populate it)
//
// if unset is off
// putconfigs pass raw fc.hideCode on e
//
//Lock the config, after setting everything to avoid changes.
//REQUIRES AN OTA/NEW FIRMWARE WITH A CODE CHANGE TO IGNORE THE SETTING TO UNDO
//must restart device after setting to make active
//
//if unset, is off, config writing allowed
//putconfigs pass raw fc.lockConf on e
//
// END OF CONFIGURATION OPTIONS
//
