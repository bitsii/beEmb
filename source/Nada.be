/*
 * Copyright (c) 2021-2023, the Beysant Embedded Authors.
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
use Embedded:Files;
use Encode:Url as EU;
use Embedded:AppShell;

class Embedded:Nada(Embedded:AppShell) {

   buildControl(Int conPos, String conName, String conArgs) {
     "Unknown control conName in Nada".print();
     return(null);
   }

}
