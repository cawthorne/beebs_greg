#!/bin/bash

cd build

make clean

cd ..

autoconf
automake

cd build

../configure --host=arm-none-eabi --with-board=stm32f0discovery --with-chip=stm32f051

make

Date="Benchmarks for $(date -u)"$'\n'

echo $Date > benchmark.txt

function ifUsable {
    if [ $1 == "src/bubblesort" ] || [ $1 == "src/dijkstra"  ] || [ $1 == "src/mergesort"  ] || [ $1 == "src/fac"  ] || [ $1 == "src/prime"  ] || [ $1 == "src/bs"  ] || [ $1 == "src/cnt"  ] || [ $1 == "src/recursion"  ] || [ $1 == "src/sqrt"  ] || [ $1 == "src/sglib-arraysort"  ] || [ $1 == "src/fibcall"  ] || [ $1 == "src/levenshtein"  ] || [ $1 == "src/ud"  ] || [ $1 == "src/select"  ] || [ $1 == "src/sglib-queue"  ] || [ $1 == "src/2dfir"  ] || [ $1 == "src/slre" ]
    then
        return 0
    else 
        return 1
    fi
}


for path in src/*; do
    ifUsable $path && [ -d "${path}" ] || continue # if not a directory, skip
    echo $path" small" | tee -a benchmark.txt
    platformrun stm32f0discovery $path${path:3}"_small" | tee -a benchmark.txt
    echo | tee -a benchmark.txt
    echo $path" medium" | tee -a benchmark.txt
    platformrun stm32f0discovery $path${path:3} | tee -a benchmark.txt
    echo | tee -a benchmark.txt
    echo $path" large" | tee -a benchmark.txt
    platformrun stm32f0discovery $path${path:3}"_large" | tee -a benchmark.txt
    echo | tee -a benchmark.txt
done





