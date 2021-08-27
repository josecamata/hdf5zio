#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
#include <typeinfo>


using namespace std;

#include "HDF5Reader.h"
HDF5Reader::HDF5Reader(const char* fileName) : HDF5Base(fileName) 
{
    //do nothing
}

void HDF5Reader::read(const char *name, int* dataBase, int size, const char* dSetName) 
{
    //check if is chuncked
    //call the right function
    readNormal(name, dataBase, size, dSetName);
}

void HDF5Reader::read(const char *name, float* dataBase, int size, const char* dSetName) 
{
    //check if is chuncked
    //call the right function
    readNormal(name, dataBase, size, dSetName);
}

void HDF5Reader::read(const char *name, double* dataBase, int size, const char* dSetName) 
{
    //check if is chuncked
    //call the right function
    readNormal(name, dataBase, size, dSetName);
}

void HDF5Reader::readNormal(const char* name, int* dataBase, int size, const char* dSetName) 
{
    hid_t  datasetId; 
    herr_t statusFileInTheFunction;
    
    fileId = H5Fopen(name, H5F_ACC_RDWR, H5P_DEFAULT);
    datasetId = H5Dopen2(fileId, dSetName, H5P_DEFAULT);

    statusFileInTheFunction = H5Dread(datasetId, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    for(int i = 0; i < size; i++){
        cout<<dataBase[i]<<"   ";
    }
    cout<<endl;

    statusFileInTheFunction = H5Dclose(datasetId);
}

void HDF5Reader::readNormal(const char* name, float* dataBase, int size, const char* dSetName) 
{
    hid_t  datasetId; 
    herr_t statusFileInTheFunction;
    
    fileId = H5Fopen(name, H5F_ACC_RDWR, H5P_DEFAULT);
    datasetId = H5Dopen2(fileId, dSetName, H5P_DEFAULT);

    statusFileInTheFunction = H5Dread(datasetId, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    for(int i = 0; i < size; i++){
        cout<<dataBase[i]<<"   ";
    }
    cout<<endl;

    statusFileInTheFunction = H5Dclose(datasetId);
}

void HDF5Reader::readNormal(const char* name, double* dataBase, int size, const char* dSetName) 
{
    hid_t  datasetId; 
    herr_t statusFileInTheFunction;
    
    fileId = H5Fopen(name, H5F_ACC_RDWR, H5P_DEFAULT);
    datasetId = H5Dopen2(fileId, dSetName, H5P_DEFAULT);

    statusFileInTheFunction = H5Dread(datasetId, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    for(int i = 0; i < size; i++){
        cout<<dataBase[i]<<"   ";
    }
    cout<<endl;

    statusFileInTheFunction = H5Dclose(datasetId);
}

/*
    typeid().name()
    int --> A3_i
    float --> A3_f
    double --> A3_d
*/