#! /run/current-system/sw/bin/bash

rm -rf build
mkdir build
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
./build/test

