#!/bin/bash

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

####
## ZFP
####
git clone https://github.com/LLNL/zfp.git 
cd zfp 
cp ../files/Config .

make
sudo mkdir /opt/lib/zfp
sudo cp -r include /opt/lib/zfp 
sudo cp -r /opt/lib/zfp
sudo cp Config /opt/lib/zfp 
cd ..

# 
# PLUGIN ZFP
#
git clone  https://github.com/LLNL/H5Z-ZFP.git
cd H5Z-ZFP 
make CC=gcc ZFP_HOME=/opt/lib/zfp HDF5_HOME=/opt/lib/hdf5 PREFIX=/opt/lib/h5z_zfp all
sudo make  CC=gcc ZFP_HOME=/opt/lib/zfp HDF5_HOME=/opt/lib/hdf5 PREFIX=/opt/lib/h5z_zfp install
cd ..
echo "Auto Install Finished!"




