#!/bin/bash
clear
mkdir build
cd build
cmake ../.
make clean all
clear
./HDF5zio.exe
cd ..