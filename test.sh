#!/bin/bash

mkdir -p build/output

for path in $(find scenes -name "*.scn")
do
    file=$(basename "$path")
    build/tp2 "$path" build/output/"${file%.*}".png
done
