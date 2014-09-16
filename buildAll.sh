#!/bin/bash

# build library
cd build
rm -rf *
cmake ..
make

cd ../buildExamples
rm -rf *
cmake -DDEPTHLIB_PATH:STRING=$1 ../Examples 
make
