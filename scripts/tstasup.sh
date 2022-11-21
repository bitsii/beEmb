#!/bin/bash

  curl 'http://192.168.1.241/u2?fsz=348272' \
  -X 'POST' \
  -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8' \
  -H 'Content-Length: 348479' \
  -H 'Accept-Language: en-US,en' \
  -H 'Cache-Control: max-age=0' \
  -H 'Connection: keep-alive' \
  --form "u2=@./bsard/bsard.ino.nodemcu.bin;type=multipart/form-data" \
  -H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/107.0.0.0 Safari/537.36'

#  -H 'Content-Type: multipart/form-data; boundary=----WebKitFormBoundary714Cwmw4HswsPg9q' \
#  -H 'Content-Length: 348479' \
#  -H 'Origin: http://192.168.1.241' \
# -H 'Referer: http://192.168.1.241/up?' \
#  -H 'Sec-GPC: 1' \
#  -H 'Upgrade-Insecure-Requests: 1' \
#  -F upload=./bsard/bsard.ino.nodemcu.bin \
