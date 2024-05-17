#!/bin/bash

black --check src/motor_platform
black_return_value=$?

if [ $black_return_value -eq 0 ]; then
  exit
else
  echo "Python format failed"
  exit 1
fi