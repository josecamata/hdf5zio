#!/bin/bash
cd ~
sudo apt install make
cd Downloads
wget -c -np https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.12/hdf5-1.12.1/src/hdf5-1.12.1.tar.gz
wget -c -np https://support.hdfgroup.org/ftp/lib-external/szip/2.1.1/src/szip-2.1.1.tar.gz
cd /opt/
sudo mkdir lib
cd ~
cd Downloads
sudo tar -vzxf szip-2.1.1.tar.gz 
sudo tar -vzxf hdf5-1.12.1.tar.gz
sudo mv szip-2.1.1 /opt/lib
sudo mv hdf5-1.12.1 /opt/lib
cd ~
cd /opt/lib/szip-2.1.1
sudo ./configure --prefix=/opt/lib/szip 
sudo make 
sudo make install
cd ~
cd /opt/lib/hdf5-1.12.1
./configure --prefix=/opt/lib/hdf5 --enable-cxx --enable-c --with-szlib=/opt/lib/szip
sudo make
sudo make install


