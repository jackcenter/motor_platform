#!/bin/bash

python3 -m unittest discover -v -s src/motor_platform
unittest_return_value=$?

if [ $unittest_return_value -eq 0 ]; then
  exit
else
  echo "Unittest failed"
  exit 1
fi