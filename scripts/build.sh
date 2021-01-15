#!/bin/sh

rm -rf build
mkdir build
cd build
qmake ../src/trading-platform-pp.pro
make -j8