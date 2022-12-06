// Copyright 2021 The BraceEmb Authors. All rights reserved.
// Use of this source code is governed by the BSD-3-Clause
// license that can be found in the LICENSE file.

use Text:Strings as TS;
use System:Exception;

class Embedded:Update {

     emit(cc_classHead) {
   """
BearSSL::PublicKey *signPubKey = nullptr;
BearSSL::HashSHA256 *hash;
BearSSL::SigningVerifier *sign;
   """
     }

  signKey(String cert) {
    emit(cc) {
      """
signPubKey = new BearSSL::PublicKey(beva_cert->bems_toCcString().c_str());
hash = new BearSSL::HashSHA256();
sign = new BearSSL::SigningVerifier(signPubKey);
      """
    }
  }

  updateFromUrl(String url) {

    emit(cc) {
     """
     if (signPubKey != nullptr) {
       Serial.println("setting update signature");
       Update.installSignature(hash, sign);
     }
     WiFiClient client;
     t_httpUpdate_return ret = ESPhttpUpdate.update(client, beva_url->bems_toCcString().c_str());
     """
    }

  }

}
