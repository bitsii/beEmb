# Bennt Embedded

<br />
<div align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/cpuinfo.png" alt="Logo" width="80" height="80">
  </a>
  </div>
  
Batteries-included firmware for the Esp8266 for home automation device construction.  Includes a secure open protocol with companion mobile applications coming soon for Wifi provisioning and device control.

Built on the Arduino platform for ease of development and rich library support.  Written in [Bennt](https://github.com/bitsii/beBase) - an object oriented, garbage collected language that transpiles to C++.  Licensed under the [BSD-2-Clause](https://opensource.org/licenses/BSD-2-Clause) open source license.

## Prebuilt solutions

Common profiles are prebuilt and can be enabled through header configuration, just specify the controls and GPIOs, see Choose your configuration below to get rolling.

Current profiles include:

* Buttons
* Switches
* Lights (and)
* Dimmers

(with more planned)

Devices can be configured to connect to Mqtt with Home Assistant Auto-Discovery (and device control) as well, to easily support the self-hosting home automation crowd.

## Plumbing is in

The "stuff to make it work" is already assembled.

* Before Wifi is configured an access point is started to accept provisioning
* Provisioning includes Wifi configuration, unique device identity and authentication tokens
* Device announces itself over mDNS using the unique identity established during provisioning.  
* An open TCP based protocol can be used to interact with the device - see [CasProt](https://github.com/bitsii/CasProt)
* MQTT details can be provided as well, and the device will announce controls consistent with it's configuration to Home Assistant and other compatible solutions
* If a device loses it's Wifi for a period of time it can be reprovisioned to a new network.
* Secure reset mechanisms available - via button long-push (on devices with buttons) or when removed from provisioned Wifi (configurable)
* OTA updates from the web are supported
* A configurable telnet addressable debug port is also supported for use during development or support of equipment without a direct serial connection

## Pragmatic Security

Security is tough, but important.  On low-power embedded devices it's necessary to build in protection while remaining within the device's performance envelope.  

Bennt Embedded tries to strike a good balance:

* All Devices start with a random configuration code - no default passwords.  An additional unannounced, pre-provisioned code can be configured in the device where needed.
* Authentication tokens are only exchanged in the clear during provisioning on the devices AP using the configuration codes.  Optional WPA support for the AP mode can provide isolation and encryption during this process if required.
* Separate Administrative and Usage tokens (created during provisioning) allow privileged users to reconfigure the device and allow unprivileged users to use a device's capabilities but not change its configuration.
* Secrets are not passed in the clear once provisioned and connected to the target wifi network.  Device commands are signed and validated with the shared secrets (the tokens) to protect against unauthorized use.  Signing includes the source network address to mitigate MITM attacks.

## Just install something already

TODO - coming soon, prebuilt binaries you can just put on the hardware.  For now you'll need to go ahead with Building my Own Thing if you want to get started

## Building my Own Thing

Maybe one of the "binaries ready to go" isn't quite ready to go for you (well, or anyone at the moment...) - perhaps you need a different configuration or deeper customization.  There are two levels available to you - one relatively simple option that works when you just need to customize the combination of controls and their in-built configuration is to just modify the config in the header and upload.  This only requires some Arduino IDE setup.  Beyond that you can modify the code itself do to whatever you want - see Further Customization for starting points there.

### Getting Ready

You'll need a working installation of the Arduino IDE with a couple of libraries installed.  

* If you don't have the IDE, see [here](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE) (note, some experience with the ecosystem is expected...)
* You'll need to install the Esp8266 boards manager - in the Arduino IDE go to Preferences, find Additional boards manager urls and add http://arduino.esp8266.com/stable/package_esp8266com_index.json .  Tested with version 3.1.1.
* [More detailed instructions for adding the Esp8266 board manager here if you need it](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/)
* You'll also need to install the Mqtt library, go to the IDE's library manager, search for [MQTT by Joel Gaehwiler](https://github.com/256dpi/arduino-mqtt).  Tested with version 2.5.1

### Get the Hardware

* Some pre-built devices are supported, including the [Athom Plug V2 US](https://www.athom.tech/blank-1/tasmota-us-plug-v2)
* Bennt Embedded should also work with most any Esp8266 development board.  2MB flash is recommended, though 1MB should work without OTA.
* If your board has built in LED's you want to use make sure you know the GPIO/pin numbers for your configuration.
* Of course, many folks will be wiring up their own solution for hobby use - pick good GPIOs for your board, connect things up, and make a note of the pin numbers.
* If you are building a product and using the firmware on it, you should be able to follow the configuration spec below to prep your build for your product.

### Check it out

Check out [the repo](https://github.com/bitsii/beEmb) with git (or choose Code/Download Zip and then extract it)

### Pick your combo

Depending on the combination of controls you need pick the sketch subdirectory that works.  You should understand your planned configuration (see Choose your configuration below) and target (a dev board or a prebuilt device) and then choose.  Prebuilt devices need a *ns (no serial) sketch as the serial input causes them to fail. There will be serial output for those with a development board, but no input (small matter).

If you want button, switch, and switch indicator support, use the sketch in the ardswbusicns subdirectory.  This is a good place to start, it is what is used for the Athom switch and works on dev boards and prebuilt devices.

So, options:

* ardswbusicns for button, switch, and switch indicator support on dev boards and prebuilt devices
* ardswdimns switch and dimmer on dev boards and prebuilt devices
* ardswns switch only on dev or prebuilt
* ardswdim if you want switch and dimmer only on a development board

Open your Arduino IDE, navigate to where you checked out beEmb, pick the subdirectory you want from the above list, and open the sketch (with the same name as it's directory).  Then, continue on to Configure for build and upload.

### Configure for build and upload

Then configure for the build, in the IDE change the following settings under the tools menu:

* Set the Board to Generic ESP8266 Module
* Set the Flash Size to 2MB (FS:64KB OTA:~992KB) (you can use 1MB FS:64KB if that's all your board has, but OTA won't work / it's a tight fit)
* Set SSL Support to Basic SSL Ciphers
* Set C++ Exceptions to Enabled
* Set the Upload Speed to 460800
* Pick your Port to which you've connected the board via USB (If building firmward to upload via the network, you can skip this)
* Generally you set the Erase Flash to Only Sketch, unless you want to clear the provisioning on a development board (in which case you can pick All Flash Contents)

Next - Choose your configuration

### Choose your configuration

* Open BEH_4_Base.hpp in the Arduino IDE (it is in the chosen directory next to the *.ino sketch, it should be already in the IDE in the side menu or as a top tab)
* At the top of the file are the configuration options, with a good deal of explanation and examples.  Refer to the information there and the details below to perform your configuration.  You'll pick one BESPEC_SW and one BESPEC_CON to define your device.
* BESPEC_SW configures the devices as it appears for provisoning, it is a string with a ConfigVersion(currently 0).An identifier (short name for your device).the device version (num > 0, you control it to version your solution for updates).  Something like #define BESPEC_SW "0.LightSwitch.99"  
* BESPEC_CON defines the controls and their order, sw is a switch, dim is a dimmer, bu is a button, and sic ties the state of one switch to another.  You should have at least one control (frequently that is all), but may have more if you have several components attached to different pins.  The leading number is a version for the definition, currently always 0.  Remaining controls are dot "." separated, with commas used to define other parameters that control understands (if any).  So  #define BESPEC_CON "0.sw.16.dim.2" would configure two controls, one on-off switch on pin 16, and one adjustable dimmer on pin 2 (those are the LED pins on a standard NodeMCU, fwiw).
* The spec for sw takes a pin parameter first and uses it to set 0 or 255 with an optional "direction" if on and off is reversed for your application.  So sw.16 sets 0 for "on" and 255 for "off" on pin 16.  To reverse the 0 and 255 values use sw.16,1 
* The spec for dim takes a pin parameter only, direction is not currently supported.  It understands on and off (and remembers the last level set, defaults to full on the first time).  It supports setting values between 0 and 254 for different light levels (0 is full on, 255 is not a dim level, it is off).
* The spec for button takes a number of parameters, it supports use both for turning on and off a switch control you have defined and resetting for a long push of a button.  bu.5,0,30,0,10000 would setup a button on pin 5, second parameter allows controlling what "on" means depending on how your button works, typical is 0 as here (1 is other option to reverse).  30 is the milliseconds the button must be held to be considered a "toggle event", the next value (0) is the position of the switch toggled by the short press of the button, this is the position in the list of controls separated by ., in this case 0, meaning a "sw" control was at the start of the config (before this bu control). If you have no sw control you want to manage with the button (maybe it is only for reset) you can put 0 in for the toggle event push time (where we have 30 here) and any value for the sw control (it's ignored). The last parameter is the length of a long push which will reset the device in milliseconds - so in this example 10 seconds (longer, like 30 seconds is better "for real") - 0 disables. The button does use pin input mode pullup on the specified pin to create a resistence - this is typically what's desired for buttons, be sure your hardware and configuration works with that (you should not have or need an additional resistor in the circuit).  "toggle" means, when the button is pushed the proper time for a toggle event, it will reverse the switch from it's current value, so an "on" switch goes off, an "off" switch goes on (as you'd expect)
* The spec for sic takes a pin to managed the on and off for first (like sw), then a direction parameter (same as sw direction parameter), then the position of the switch to "watch" in the order of controls (like bu).  It will then watch for that switch to turn off or on and match it's own state to that switch.  sic.16,0,0 would control pin 16, using the "standard direction" (0), looking at the first control in the configuration (which would need to be an sw) and matching it's state to that sw controls state.

### Burn it

Finally, choose Sketch / Upload in the Arduino IDE to put it on your device.  (Coming soon - how to load it onto a prebuilt device with a different firmware)

### Further Customization

If you need your controls to behave differently than they do out of the box, or you want to create your own new controls, you'll also need to setup a Bennt development environment and checkout/modify/build the actual project (the downloaded sketches are pre-generated and only support configuration based customization - you'll need to have the above Arduino environment setup and working, and then you can go further with the instructions below)

First you need to setup the Bennt language, see [The Bennt Project](https://github.com/bitsii/beBase) for that.  The java environment is sufficient.

then, from the directory containing "beBase" (where you cloned it, not the beBase directory itself, the one above it), clone beEmb
(from your shell / on MSWin from the git shell you installed)

git clone https://github.com/bitsii/beEmb
cd beEmb

From your beEmb directory you run different scripts depending on the combination of controls you want to support.

* ./scripts/swns.sh supports a switch but no serial input (needed for non-development-board devices, fine with dev boards too). Generates into ardswns
* ./scripts/swdimns.sh supports a switch and dimmer without serial input, good for dev boards and prebuilt. Generates into ardswdimns
* ./scripts/swdim.sh supports a switch and dimmer with serial input (only for development boards). Generates into ardswdim
* ./scripts/swbusicns.sh supports switch, button, dimmer with no serial input (fine for non-dev-boards and dev boards, the script used for the packaging for the Athom Plug).  Generates into ardswbusicns

More may be added, obviously not all combinations are there, just the ones needed so far.  Some comparison and mixing and matching will allow you to put together other combos as you need them.

When working in this mode you should setup your configuration for BESPEC_SW and BESPEC_CON in the system/cc/be/BEAR_Conf.hpp file BEFORE running the generator script instead of afterwards in the BEH_4_Base.hpp as the latter will be over written at every generation with the contents of the former (configuration works the same way, of course). Run the appropriate script, it should generate the code.  Look at the BC.be, DC.be, SC.be, SIC.be files for the control code.  SH.be is the "main app code", other files are there for the Wifi, etc.  You may need to work with the code a bit to learn how it works, feel free to reach out with questions.  When you make changes re-run the appropriate generator script to regenerate the C++ for the Arduino IDE, it will generate into the ard subdirectory in the project.  When you are ready to build and upload open the Arduino IDE, open the sketch in the subdirectory of the project for the script that you ran (see above), and choose Sketch/Upload to upload the sketch to the board as you normally would.

The official list of Bennt Embedded Authors:

Craig Welch <mebitsii@gmail.com>
