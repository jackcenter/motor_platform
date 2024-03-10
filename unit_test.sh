#!/bin/bash

mkdir build; cd build
cmake ..; cmake --build .
ctest --verbose
ctest_return_value=$?

if [ $ctest_return_value -eq 0 ]; then
  exit
else
  echo "CTest failed."
  exit 1
fi
