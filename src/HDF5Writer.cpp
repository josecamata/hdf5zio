#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

#include "HDF5Writer.h"

HDF5Writer::HDF5Writer(const char* fileName)
: HDF5Base(fileName) 
{
    this->c = NOCOMPRESSION;
}

void HDF5Writer::write(int* dataBase, int size, const char* dSetName)
{
    switch (this->c)
    {
    case ZLIB:
        /* code */
        break;
    case SZIP:
        /**/
        break;
    default:
        writeNormal(dataBase, size, dSetName);
        break;
    }
}

void HDF5Writer::write(float* dataBase, int size, const char* dSetName) 
{
    switch (this->c)
    {
    case ZLIB:
        /* code */
        break;
    case SZIP:
        /**/
        break;
    default:
        writeNormal(dataBase, size, dSetName);
        break;
    }
}

void HDF5Writer::write(double* dataBase, int size, const char* dSetName) 
{

    switch (this->c)
    {
    case ZLIB:
        /* code */
        break;
    case SZIP:
        /**/
        break;
    default:
        writeNormal(dataBase, size, dSetName);
        break;
    }

}

void HDF5Writer::setCompression(CompressionType c) 
{
    this->c = c;
}

void HDF5Writer::writeNormal(int* dataBase, int size, const char* dSetName) 
{
    herr_t statusFileInTheFunction;
    hsize_t dims[1];
    hid_t datasetId;
    hid_t dataspaceId;
    dims[0] = size;

    fileId = H5Fcreate(fileName, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    dataspaceId = H5Screate_simple(1, dims, NULL);

    datasetId = H5Dcreate2(fileId, dSetName, H5T_NATIVE_INT, dataspaceId, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    statusFileInTheFunction = H5Dwrite(datasetId, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    /*End acces to the dataset and release resources used by it*/
    statusFileInTheFunction = H5Dclose(datasetId);

    /*Terminate access to the data space*/
    statusFileInTheFunction = H5Sclose(dataspaceId);
}

void HDF5Writer::writeNormal(float* dataBase, int size, const char* dSetName)
{
    herr_t statusFileInTheFunction;
    hsize_t dims[1];
    hid_t datasetId;
    hid_t dataspaceId;
    dims[0] = size;

    fileId = H5Fcreate(fileName, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    dataspaceId = H5Screate_simple(1, dims, NULL);
    
    datasetId = H5Dcreate2(fileId, dSetName, H5T_NATIVE_FLOAT, dataspaceId, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    statusFileInTheFunction = H5Dwrite(datasetId, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    /*End acces to the dataset and release resources used by it*/
    statusFileInTheFunction = H5Dclose(datasetId);

    /*Terminate access to the data space*/
    statusFileInTheFunction = H5Sclose(dataspaceId);
}


void HDF5Writer::writeNormal(double* dataBase, int size, const char* dSetName) 
{
    herr_t statusFileInTheFunction;
    hsize_t dims[1];
    hid_t datasetId;
    hid_t dataspaceId;
    dims[0] = size;

    fileId = H5Fcreate(fileName, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    dataspaceId = H5Screate_simple(1, dims, NULL);
    
    datasetId = H5Dcreate2(fileId, dSetName, H5T_NATIVE_DOUBLE, dataspaceId, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    statusFileInTheFunction = H5Dwrite(datasetId, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    /*End acces to the dataset and release resources used by it*/
    statusFileInTheFunction = H5Dclose(datasetId);

    /*Terminate access to the data space*/
    statusFileInTheFunction = H5Sclose(dataspaceId);
}



void HDF5Writer::writeChuncked(int* dataBase, int size, const char* dSetName) 
{
    cout<<"Em manutenção"<<endl;
}

/*
TODO ask Camata which one to use and what's the difference between H5T_NATIVE_DOUBLE_g and H5T_NATIVE_DOUBLE (float also has them both)
*/