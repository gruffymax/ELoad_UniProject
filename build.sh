#!/bin/bash
# Setup Arm Compiler Environment and invoke CMake
# By Gareth Waymark 02/2021

export PATH=/opt/gcc-arm-none-eabi-10-2020-q4-major/bin:$PATH
cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake .
make -j4
