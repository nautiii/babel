#!/bin/bash

rm -rf build babel_server babel_client
mkdir build
cd build
conan install .. --build=missing
cmake ..
make -j4
mv bin/babel_server bin/babel_client ..
cd ..
rm -rf build