# Brace Embedded

<br />
<div align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/cpuinfo.png" alt="Logo" width="80" height="80">
  </a>
  </div>
  
Batteries-included firmware for the Esp8266 and ESP32 targeted for home automation use cases.  Pairs well with an [open source application](https://gitlab.com/bitsii/CasCon) for connecting devices running the firmware to your network and controlling them - get [started here](https://gitlab.com/bitsii/CasCon/-/wikis/Casnic)

Built on the Arduino platform, written in [Brace](https://github.com/bitsii/beBase) - an object oriented, garbage collected language that transpiles to C++.  Licensed under the [BSD-2-Clause](https://opensource.org/licenses/BSD-2-Clause) open source license.

## Prebuilt solutions

Common profiles are ready to go and can be customized through header configuration, including:

* On/Off Switches
* RGBCW LED Lights

(with more planned)

## Features

* Device and [the application](https://gitlab.com/bitsii/CasCon) support [device provisioning to Wifi network and device control](https://gitlab.com/bitsii/CasCon/-/wikis/Casnic) all in the mobile app.
* Device announces itself over mDNS
* Configuration and usage supported an open TCP based protocol
* Reset mechanisms available - via button long-push (on devices with buttons) or specific power cycling pattern. See [device reset](https://gitlab.com/bitsii/CasCon/-/wikis/Casnic#resetting-a-device)
* OTA updates
* Integrations and hubs to support [Voice Assistants](https://gitlab.com/bitsii/CasCon/-/wikis/Pairing-Voice-Bridge), [Home Automation Platforms](https://gitlab.com/bitsii/CasCon/-/wikis/Working-with-other-home-automation-hubs), [Remote Access](https://gitlab.com/bitsii/CasCon/-/wikis/Remote-Access), and more.
* Device profies can be configured for different control combinations and GPIO selection through configuration in a C++ header
* Intended to feel a less served niche for everyday users, power users, and device makers - [learn about the project goals here](https://gitlab.com/bitsii/CasCon/-/wikis/Why-Casnic)

## Building on Brace Embedded

### Get the Hardware

* [Some pre-built devices are supported](https://gitlab.com/bitsii/CasCon/-/wikis/Flashable-Devices) - see the foregoing link for options and flashing instructions.
* Brace Embedded should also work with most any Esp8266 or ESP32 development board.  2MB flash is recommended for 8266, 4 or 8 depending on the device profile for esp32.

### Build your firmware

Brace Embedded is intended to be an open platform and encourages developers to build solutions on top of the device provisioning and control options available in conjunction with the [Casnic Application](https://gitlab.com/bitsii/CasCon).

As with the user experience, the goal is to provide device makers with the lowest friction possible for simple cases and easy transition into more extensive customization when called for.

[See the developer guide to learn about your options](https://gitlab.com/bitsii/beEmb/-/wikis/Developers-Guide)

## Pragmatic Security

Brace Embedded tries to strike a good balance in the security space by enforcing only authorized use while remaining performant and reliable:

* Devices start with a unique configuration code - no default passwords.
* Authentication tokens are only exchanged in the clear during provisioning on the devices AP using the configuration codes.  Optional WPA support for the AP mode can provide isolation and encryption during this process if required.
* Secrets are not passed in the clear once provisioned and connected to the target wifi network.  Device commands are signed and validated with the shared secrets (the tokens) to protect against unauthorized use.  Signing includes the source network address to mitigate MITM attacks and time elements to resist replay attacks.
* Separate Administrative and Usage tokens (created during provisioning) are required for device control and use.  Users with the administrative token can configure the device and users with the usage token can only use the configured features (turn on and off, etc)  The application supports [sharing](https://gitlab.com/bitsii/CasCon/-/wikis/Casnic#sharing-a-device) to grant new users and devices access.

## Be Careful

Use of this information and the software is entirely at your own risk.  As with any interaction between software and something "acting in the real world" or "running electricity around", be sure system failure or unexpected behavior cannot result in harm or injury to anyone or anything.

## Credits

The official list of Brace Embedded Authors:

Craig Welch <bitsiiway@gmail.com>
