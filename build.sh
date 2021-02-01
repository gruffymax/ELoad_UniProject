# Setup Arm Compiler Environment and invoke CMake
# By Gareth Waymark 02/2021

source ~/scripts/arm-environment.sh
cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake .
make -j4
