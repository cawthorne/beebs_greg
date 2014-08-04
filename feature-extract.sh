#!/bin/bash

Date="Feature Extraction for $(date -u)"

echo $Date > features.txt


for path in src/*; do
    [ -d "${path}" ] || continue # if not a directory, skip
    echo "new Benchmark" | tee -a features.txt
    echo $path | tee -a features.txt
    for file in $path/*.c; do
        [ -f "${file}" ] || continue # if not a file, skip
        echo "newFile" | tee -a features.txt
        echo $file | tee -a features.txt
        sed -e s/'#include "support.h"'/""/g -e s/"REPEAT_FACTOR"/"255"/g $file > featExtract.c
        gcc-4.9 -I$path -fplugin=mageec featExtract.c -lm |& tee -a features.txt
    done
    echo | tee -a features.txt
done

rm -f -r featExtract.c