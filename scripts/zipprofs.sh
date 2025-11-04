#!/bin/bash

mkdir -p genned
rm -f genned/casnic_profiles.zip

zip -r genned/casnic_profiles.zip pfonoff pfonoffser pfrgbcw pfrgbcwser

echo "Zip is genned/casnic_profiles.zip"
