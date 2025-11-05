#!/bin/bash

mkdir -p genned
rm -f genned/casnic_profiles.zip

zip -r genned/casnic_profiles.zip pfonoff pfonoffser pfrgbcw pfrgbcwser pfn32blb pfn32blbbl pfn32plg pfn32plgser

echo "Zip is genned/casnic_profiles.zip"
