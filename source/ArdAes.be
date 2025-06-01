/*
 * Copyright (c) 2015-2023, the Brace App Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

use Text:Strings as TS;
use System:Exception;

class Embedded:Aes {

  new() self {
    fields {
      Int keyLength = 16;
      Int ivLength = 16;
    }
  }
  
  encrypt(String iv, String key, String val) String {
    iv = iv.substring(0, ivLength);
    key = key.substring(0, keyLength);//jv limit
    val = val.substring(0, val.length);
    String res;
    emit(cc) {
    """  
  //uint8_t cipher_key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5};
  //uint8_t cipher_iv[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5};
  unsigned char* cipher_key = beq->beva_key->bevi_bytes.data();
  unsigned char* cipher_iv = beq->beva_iv->bevi_bytes.data();
  
  //String plain_data = "quick brown fox jumps over the lazy dog";
  String plain_data = beq->beva_val->bems_toCcString().c_str();
  int i;
  // PKCS#7 Padding (Encryption), Block Size : 16
  int len = plain_data.length();
  int n_blocks = len / 16 + 1;
  uint8_t n_padding = n_blocks * 16 - len;
  uint8_t data[n_blocks*16];
  memcpy(data, plain_data.c_str(), len);
  for(i = len; i < n_blocks * 16; i++){
    data[i] = n_padding;
  }
  
  uint8_t key[16], iv[16];
  memcpy(key, cipher_key, 16);
  memcpy(iv, cipher_iv, 16);

  // encryption context
  br_aes_big_cbcenc_keys encCtx;

  // reset the encryption context and encrypt the data
  br_aes_big_cbcenc_init(&encCtx, key, 16);
  br_aes_big_cbcenc_run( &encCtx, iv, data, n_blocks*16 );
  
  int32_t finlen = n_blocks*16;
  unsigned char* x = data;
  
  std::vector<unsigned char>sdata(x, x + finlen);
  beq->bevl_res = new BEC_2_4_6_TextString(finlen, sdata);
    """
    }
    return(res);
  }
  
  decrypt(String iv, String key, String val) String {
    iv = iv.substring(0, ivLength);
    key = key.substring(0, keyLength);//jv limit
    val = val.substring(0, val.length);
    Int len = val.length;
    String res;
    emit(cc) {
    """
  //uint8_t cipher_key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5};
  //uint8_t cipher_iv[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5};
  unsigned char* cipher_key = beq->beva_key->bevi_bytes.data();
  unsigned char* cipher_iv = beq->beva_iv->bevi_bytes.data();

  int len = beq->bevl_len->bevi_int;
  std::vector<unsigned char> vdata = beq->beva_val->bevi_bytes;
  unsigned char* cdata = vdata.data();

  uint8_t key[16], iv[16];
  memcpy(key, cipher_key, 16);
  memcpy(iv, cipher_iv, 16);

  int n_blocks = len / 16;

  br_aes_big_cbcdec_keys decCtx;

  br_aes_big_cbcdec_init(&decCtx, key, 16);
  br_aes_big_cbcdec_run( &decCtx, iv, cdata, n_blocks*16 );
  
  uint8_t n_padding = cdata[n_blocks*16-1];
  len = n_blocks*16 - n_padding;
  char plain_data[len];
  memcpy(plain_data, cdata, len);
  
  std::vector<unsigned char>sdata(plain_data, plain_data + len);
  beq->bevl_res = new BEC_2_4_6_TextString(len, sdata);
  
    """
    }
    return(res);
  }

}