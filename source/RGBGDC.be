/*
 * Copyright (c) 2021-2023, the Brace Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Math:Int;
use Embedded:Wifi;
use Text:String;
use Text:Strings as TS;
use Embedded:AppShell;
use Embedded:Config;

class Embedded:RGBGamDimCon(Embedded:RGBControl) {

   new(_ash, Int _conPos, String _conName, String _conArgs) {
     super.new(_ash, _conPos, _conName, _conArgs);
     conType = "rgbdim";
   }

   initControl() {
     super.initControl();
   }

   doState(List cmdl) String {
     return(super.doState(cmdl));
   }

   clearStates() {
     super.clearStates();
   }
   
}
