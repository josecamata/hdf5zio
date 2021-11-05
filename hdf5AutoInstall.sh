#!/bin/bash
cd ~
mkdir tmp_hdf5
cd tmp_hdf5 
wget -c -np https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.12/hdf5-1.12.1/src/hdf5-1.12.1.tar.gz
wget -c -np https://support.hdfgroup.org/ftp/lib-external/szip/2.1.1/src/szip-2.1.1.tar.gz
tar -vzxf szip-2.1.1.tar.gz 
tar -vzxf hdf5-1.12.1.tar.gz
cd szip-2.1.1
./configure --prefix=/opt/lib/szip 
make 
sudo make install
cd ..
cd hdf5-1.12.1
./configure --prefix=/opt/lib/hdf5 --enable-cxx --enable-c --with-szlib=/opt/lib/szip
make
sudo make install
cd ~
rm -rf tmp_hdf5 

