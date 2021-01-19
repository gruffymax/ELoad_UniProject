#Clean
rm -rf CMakeFiles
rm -f CMakeCache.txt
rm -f cmake_install.cmake
rm -f Makefile

#CMake
cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake .
make -j4
