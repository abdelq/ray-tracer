#!/bin/bash

mkdir -p build/output/diff

for path in $(find scenes -name "*.scn")
do
    file=$(basename "$path")
    (build/tp2 "$path" build/output/"${file%.*}".png &&
        compare -compose src ../imageReferences/"${file%.*}".png build/output/"${file%.*}".png build/output/diff/"${file%.*}".png) &
done
