/*
 * Copyright (c) 2021-2023, the Bennt Embedded Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Text:Strings as TS;
use System:Exception;

class Embedded:Update {

  updateFromUrl(String url) {

    Int res = Int.new();
    emit(cc) {
     """
     Serial.println("gonna update");
     WiFiClient client;
     t_httpUpdate_return ret = ESPhttpUpdate.update(client, beq->beva_url->bems_toCcString().c_str());
     Serial.println("return ret");
     Serial.println(ESPhttpUpdate.getLastError());
     Serial.println(ESPhttpUpdate.getLastErrorString());
     """
    }

  }

}
