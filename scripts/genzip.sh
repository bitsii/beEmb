#!/bin/bash

export ZZDN=$1

mkdir -p genned

gzip -9kf ${ZZDN}/*.bin
rm genned/${ZZDN}.zip
zip genned/${ZZDN}.zip ${ZZDN}/*
