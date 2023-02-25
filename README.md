
beEmb is a project to support the Brickle programming language https://gitlab.com/bitsii/beBase
on embedded microcontrollers for IOT/HomeAutomation (and other) applications.  Brickle is an
object oriented garbage collected programming lanugage and runtime built as a self-hosted
source to source transpiler supporting several output languages.  At present the popular
esp8266 is supported using the Arduino environment with Brickle generating C++.

First you have to have already setup the Brickle language environment, see
https://gitlab.com/bitsii/beBase (Getting Started in Readme.md) for that  (the Brickle 
  java environment should be enough)

then, from the directory containing "beBase" (where you cloned it, not the beBase 
  directory itself, the one above it), clone beEmb
(from your shell / on MSWin from the git shell you installed)

git clone https://gitlab.com/bitsii/beEmb
cd beEmb

Then, make sure you have the Arduino installed (https://www.arduino.cc/en/software)
and the esp8266 Arduino support installed as well https://github.com/esp8266/Arduino

You'll also need a compatible board.  Pretty much any esp8266/ex/8285 board will work, a good
choice might be the NodeMCU line (esp12e).

First, build the project - from your beEmb directory run ./scripts/nodemculeds8266.sh
Then, open the ard.ino in beEmb/ard in your Arduino IDE. Make sure your your Arduino IDE setup properly for the board.
Defaults are generally fine with the exception that you need to enable C++ exceptions support
under Tools/C++ exceptions (in the Arduino IDE).  The control spec in NodeMcuLeds.be defines the switch and dimmer settings and their pins - adjust them to match your boards (led) pin numbers and on/off vs dimmable configuration.  Re-reun ./scripts/nodemculeds8266.sh if you make changes (it's recommended you go to File / Prefereces in the Arduino IDE and pick "Use External Editor" and then use an external editor to make changest to the .be files under source.  You rerun the nodemculeds.sh script after any changes to regenerate the C++ for the Arduino IDE).  When you are ready choose Sketch/Verify-Compile and Sketch/Upload to upload the sketch to the board as you normally would with arduino.

TODO add how to connect to the initial access point, connect to the network, etc, etc

beEmb is a framework written in the [Brickle](https://gitlab.com/bitsii/beBase) programming language licensed under the [BSD-3-Clause](https://opensource.org/licenses/BSD-3-Clause) open source license.
