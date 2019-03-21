#!/bin/bash

if [ ! -d "$cmake-build" ]; then
  mkdir cmake-build
fi

cmake CMakeLists.txt -B cmake-build

$CURRENT=$(pwd)

cd cmake-build
make
cd $CURRENT