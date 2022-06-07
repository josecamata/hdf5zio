#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
#include <typeinfo>


using namespace std;

#include "HDF5Reader.h"
#include "zlib.h"
HDF5Reader::HDF5Reader(const char* fileName) : HDF5Base(fileName) 
{
    fileId = H5Fopen(fileName, H5F_ACC_RDWR, H5P_DEFAULT);
    //do nothing
}

void HDF5Reader::read(int* dataBase, int size, const char* dSetName) 
{

    hid_t datasetId = H5Dopen(fileId, dSetName, H5P_DEFAULT);
    H5Z_filter_t filter_type;
    hid_t plist_id;
    int i, j, numfilt;
    size_t nelmts;
    unsigned flags, filter_info;

    plist_id = H5Dget_create_plist(datasetId);

    numfilt = H5Pget_nfilters(plist_id);

    if(numfilt != 0){
        for(i = 0; i < numfilt; i++){
            nelmts = 0;
            filter_type = H5Pget_filter2(plist_id, i, &flags, &nelmts, NULL, 0, NULL, &filter_info);

            switch (filter_type)
            {
            case H5Z_FILTER_DEFLATE :
                readNormal(dataBase, size, dSetName);
                break;
            
            case H5Z_FILTER_SZIP:
                readChuncked(dataBase, size, dSetName);
                break;

            case H5Z_FILTER_ZFP:
                readChuncked(dataBase, size, dSetName);
                break;
            default:
                break;
            }
        }
    }
    else{
        readNormal(dataBase, size, dSetName);
    }
}

void HDF5Reader::read(float* dataBase, int size, const char* dSetName) 
{
    hid_t datasetId = H5Dopen(fileId, dSetName, H5P_DEFAULT);
    H5Z_filter_t filter_type;
    hid_t plist_id;
    // herr_t statusFileInTheFunction;
    int i, j, numfilt;
    size_t nelmts;
    unsigned flags, filter_info;

    plist_id = H5Dget_create_plist(datasetId);

    numfilt = H5Pget_nfilters(plist_id);
    
    if(numfilt != 0){
        for(i = 0; i < numfilt; i++){
            nelmts = 0;
            filter_type = H5Pget_filter2(plist_id, i, &flags, &nelmts, NULL, 0, NULL, &filter_info);

            switch (filter_type)
            {
            case H5Z_FILTER_DEFLATE :
                readNormal(dataBase, size, dSetName);
                break;
            
            case H5Z_FILTER_SZIP:
                readChuncked(dataBase, size, dSetName);
                break;

            case H5Z_FILTER_ZFP:
                readChuncked(dataBase, size, dSetName);
                break;

            default:
                break;
            }
        }
    }
    else{
        readNormal(dataBase, size, dSetName);
    }
}

void HDF5Reader::read(double* dataBase, int size, const char* dSetName) 
{
    hid_t datasetId = H5Dopen(fileId, dSetName, H5P_DEFAULT);
    H5Z_filter_t filter_type;
    hid_t plist_id;
    herr_t statusFileInTheFunction;
    int i, j, numfilt;
    size_t nelmts;
    unsigned flags, filter_info;
    

    plist_id = H5Dget_create_plist(datasetId);

    numfilt = H5Pget_nfilters(plist_id);

    if(numfilt != 0){
        for(i = 0; i < numfilt; i++){
            nelmts = 0;
            filter_type = H5Pget_filter2(plist_id, i, &flags, &nelmts, NULL, 0, NULL, &filter_info);

            switch (filter_type)
            {
            case H5Z_FILTER_DEFLATE :
                readNormal(dataBase, size, dSetName);
                break;
            
            case H5Z_FILTER_SZIP:
                readChuncked(dataBase, size, dSetName);
                break;

            case H5Z_FILTER_ZFP:
                readChuncked(dataBase, size, dSetName);
                break;
            
            default:
                break;
            }
        }
    }
    else{
        readNormal(dataBase, size, dSetName);
    }
}

void HDF5Reader::readNormal(int* dataBase, int size, const char* dSetName) 
{
    hid_t  datasetId; 
    herr_t statusFileInTheFunction;
    
    
    datasetId = H5Dopen2(fileId, dSetName, H5P_DEFAULT);

    statusFileInTheFunction = H5Dread(datasetId, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInTheFunction = H5Dclose(datasetId);
}

void HDF5Reader::readNormal(float* dataBase, int size, const char* dSetName) 
{
    hid_t  datasetId; 
    herr_t statusFileInTheFunction;
    
    datasetId = H5Dopen2(fileId, dSetName, H5P_DEFAULT);
    statusFileInTheFunction = H5Dread(datasetId, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInTheFunction = H5Dclose(datasetId);
}

void HDF5Reader::readNormal(double* dataBase, int size, const char* dSetName) 
{
    hid_t  datasetId; 
    herr_t statusFileInTheFunction;

    datasetId = H5Dopen2(fileId, dSetName, H5P_DEFAULT);

    statusFileInTheFunction = H5Dread(datasetId, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInTheFunction = H5Dclose(datasetId);
}

void HDF5Reader::readChuncked(double* dataBase, int size, const char* dSetName) 
{
    
    hid_t datasetId = H5Dopen(fileId, dSetName, H5P_DEFAULT);
    herr_t statusFileInTheFunction;

    statusFileInTheFunction = H5Dread(datasetId, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInTheFunction = H5Dclose(datasetId);
}

void HDF5Reader::readChuncked(int* dataBase, int size, const char* dSetName) 
{
    
    hid_t datasetId = H5Dopen(fileId, dSetName, H5P_DEFAULT);
    herr_t statusFileInTheFunction;

    statusFileInTheFunction = H5Dread(datasetId, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInTheFunction = H5Dclose(datasetId);
}

void HDF5Reader::readChuncked(float* dataBase, int size, const char* dSetName) 
{
    
    hid_t datasetId = H5Dopen(fileId, dSetName, H5P_DEFAULT);
    herr_t statusFileInTheFunction;

    statusFileInTheFunction = H5Dread(datasetId, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInTheFunction = H5Dclose(datasetId);
}

/*
    typeid().name()
    int --> A3_i
    float --> A3_f
    double --> A3_d
*/