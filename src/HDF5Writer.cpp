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

    fileId = H5Fcreate(fileName, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
}

void HDF5Writer::write(int* dataBase, int size, const char* dSetName, int zfpmode, uint* prec)
{
    switch (this->c)
    {
    case ZLIB:
        writeChunckedZLIB(dataBase, size, dSetName);
        break;
    case SZIP:
        writeChunckedSZIP(dataBase, size, dSetName);
        break;
    case ZFP:
        writeChunckedZFP(dataBase, size, dSetName, zfpmode, prec);
        break;
    default:
        writeNormal(dataBase, size, dSetName);
        break;
    }
}

void HDF5Writer::write(float* dataBase, int size, const char* dSetName, int zfpmode, uint* prec) 
{
    switch (this->c)
    {
    case ZLIB:
        writeChunckedZLIB(dataBase, size, dSetName);
        break;
    case SZIP:
        writeChunckedSZIP(dataBase, size, dSetName);
        break;
    case ZFP:
        writeChunckedZFP(dataBase, size, dSetName, zfpmode, prec);
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
        writeChunckedZLIB(dataBase, size, dSetName);
        break;
    case SZIP:
        writeChunckedSZIP(dataBase, size, dSetName);
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

    

    dataspaceId = H5Screate_simple(1, dims, NULL);
    
    datasetId = H5Dcreate2(fileId, dSetName, H5T_NATIVE_DOUBLE, dataspaceId, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    statusFileInTheFunction = H5Dwrite(datasetId, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    /*End acces to the dataset and release resources used by it*/
    statusFileInTheFunction = H5Dclose(datasetId);

    /*Terminate access to the data space*/
    statusFileInTheFunction = H5Sclose(dataspaceId);
}

void HDF5Writer::writeChunckedSZIP(int* dataBase, int size, const char* dSetName) 
{

    herr_t statusFileInFunction;
    hid_t datasetId;
    hid_t dataspaceId;
    hsize_t dims[1];
    hsize_t cdims[1];

    hid_t plistId;

    size_t nelmts;
    unsigned flags;
    unsigned filterInfo;
    H5Z_filter_t filterType;

    unsigned szip_options_mask;
    unsigned szip_pixels_per_block;

    dims[0] = size;
    cdims[0] = size;

    int i, j, numfilt;

    // char newDSetName[85] = "Compressed_";
    // strcat(newDSetName,dSetName);

    

    dataspaceId = H5Screate_simple(1, dims, NULL);

    plistId = H5Pcreate(H5P_DATASET_CREATE);

    statusFileInFunction = H5Pset_chunk(plistId, 1, cdims);

    szip_options_mask = H5_SZIP_NN_OPTION_MASK;
    szip_pixels_per_block = 2;
    statusFileInFunction = H5Pset_szip(plistId, szip_options_mask, szip_pixels_per_block);

    datasetId = H5Dcreate2(fileId, dSetName, H5T_STD_I32BE, dataspaceId, H5P_DEFAULT, plistId, H5P_DEFAULT);

    statusFileInFunction = H5Dwrite(datasetId, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInFunction = H5Sclose(dataspaceId);
    statusFileInFunction = H5Dclose(datasetId);
    statusFileInFunction = H5Pclose(plistId);


}

void HDF5Writer::writeChunckedZFP(int* dataBase, int size, const char* dSetName, int zfpmode, uint* prec)
{
    hid_t plistId;
    hid_t dataspaceId;
    hid_t datasetId;
    herr_t statusFileInFunction;

    hsize_t dims[1];
    hsize_t cdims[1];

    dims[0] = size;
    cdims[0] = size;

    plistId = H5Pcreate(H5P_DATASET_CREATE);
    statusFileInFunction = H5Pset_chunk(plistId, 1, cdims);

    H5Z_zfp_initialize();

    if (zfpmode == H5Z_ZFP_MODE_REVERSIBLE) {
        statusFileInFunction = H5Pset_zfp_reversible(plistId);
    } else if (zfpmode == H5Z_ZFP_MODE_PRECISION) {
        statusFileInFunction = H5Pset_zfp_precision(plistId, *prec);
    }

    dataspaceId = H5Screate_simple(1, dims, NULL);

    datasetId = H5Dcreate2(fileId, dSetName, H5T_STD_I32BE, dataspaceId, H5P_DEFAULT, plistId, H5P_DEFAULT);

    statusFileInFunction = H5Dwrite(datasetId, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInFunction = H5Sclose(dataspaceId);
    statusFileInFunction = H5Dclose(datasetId);
    statusFileInFunction = H5Pclose(plistId);
}

void HDF5Writer::writeChunckedZFP(float* dataBase, int size, const char* dSetName, int zfpmode, uint* prec)
{
    hid_t plistId;
    hid_t dataspaceId;
    hid_t datasetId;
    herr_t statusFileInFunction;

    hsize_t dims[1];
    hsize_t cdims[1];

    dims[0] = size;
    cdims[0] = size;

    plistId = H5Pcreate(H5P_DATASET_CREATE);
    statusFileInFunction = H5Pset_chunk(plistId, 1, cdims);

    H5Z_zfp_initialize();

    if (zfpmode == H5Z_ZFP_MODE_REVERSIBLE) {
        statusFileInFunction = H5Pset_zfp_reversible(plistId);
    } else if (zfpmode == H5Z_ZFP_MODE_PRECISION) {
        statusFileInFunction = H5Pset_zfp_precision(plistId, *prec);
    }

    dataspaceId = H5Screate_simple(1, dims, NULL);

    datasetId = H5Dcreate2(fileId, dSetName, H5T_IEEE_F64BE, dataspaceId, H5P_DEFAULT, plistId, H5P_DEFAULT);

    statusFileInFunction = H5Dwrite(datasetId, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInFunction = H5Sclose(dataspaceId);
    statusFileInFunction = H5Dclose(datasetId);
    statusFileInFunction = H5Pclose(plistId);
}

void HDF5Writer::writeChunckedZLIB(int* dataBase, int size, const char* dSetName) 
{


    herr_t statusFileInFunction;
    hid_t datasetId;
    hid_t dataspaceId;
    hsize_t dims[1];
    hsize_t cdims[1];

    hid_t plistId;

    size_t nelmts;
    unsigned flags;
    unsigned filterInfo;
    H5Z_filter_t filterType;

    dims[0] = size;
    cdims[0] = size;

    // char newDSetName[85] = "Compressed_";
    // strcat(newDSetName,dSetName);

    int i, j, numfilt;


    dataspaceId = H5Screate_simple(1, dims, NULL);

    plistId = H5Pcreate(H5P_DATASET_CREATE);

    statusFileInFunction = H5Pset_chunk(plistId, 1, cdims);
    statusFileInFunction = H5Pset_deflate(plistId, 6); //6 is the level of compression ("aggression")

    datasetId = H5Dcreate2(fileId, dSetName, H5T_STD_I32BE, dataspaceId, H5P_DEFAULT, plistId, H5P_DEFAULT);

    statusFileInFunction = H5Dwrite(datasetId, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInFunction = H5Sclose(dataspaceId);
    statusFileInFunction = H5Dclose(datasetId);
    statusFileInFunction = H5Pclose(plistId);


}

void HDF5Writer::writeChunckedSZIP(float* dataBase, int size, const char* dSetName) 
{


    herr_t statusFileInFunction;
    hid_t datasetId;
    hid_t dataspaceId;
    hsize_t dims[1];
    hsize_t cdims[1];

    hid_t plistId;

    size_t nelmts;
    unsigned flags;
    unsigned filterInfo;
    H5Z_filter_t filterType;

    unsigned szip_options_mask;
    unsigned szip_pixels_per_block;

    dims[0] = size;
    cdims[0] = size;

    int i, j, numfilt;

    // char newDSetName[85] = "Compressed_";
    // strcat(newDSetName,dSetName);

    dataspaceId = H5Screate_simple(1, dims, NULL);

    plistId = H5Pcreate(H5P_DATASET_CREATE);

    statusFileInFunction = H5Pset_chunk(plistId, 1, cdims);

    szip_options_mask = H5_SZIP_NN_OPTION_MASK;
    szip_pixels_per_block = 16;
    statusFileInFunction = H5Pset_szip(plistId, szip_options_mask, szip_pixels_per_block);

    datasetId = H5Dcreate(fileId, dSetName, H5T_IEEE_F64BE, dataspaceId, H5P_DEFAULT, plistId, H5P_DEFAULT);

    statusFileInFunction = H5Dwrite(datasetId, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInFunction = H5Sclose(dataspaceId);
    statusFileInFunction = H5Dclose(datasetId);
    statusFileInFunction = H5Pclose(plistId);


}

void HDF5Writer::writeChunckedZLIB(float* dataBase, int size, const char* dSetName) 
{


    herr_t statusFileInFunction;
    hid_t datasetId;
    hid_t dataspaceId;
    hsize_t dims[1];
    hsize_t cdims[1];

    hid_t plistId;

    size_t nelmts;
    unsigned flags;
    unsigned filterInfo;
    H5Z_filter_t filterType;

    dims[0] = size;
    cdims[0] = size;

    // char newDSetName[85] = "Compressed_";
    // strcat(newDSetName,dSetName);

    int i, j, numfilt;


    dataspaceId = H5Screate_simple(1, dims, NULL);

    plistId = H5Pcreate(H5P_DATASET_CREATE);

    statusFileInFunction = H5Pset_chunk(plistId, 1, cdims);
    statusFileInFunction = H5Pset_deflate(plistId, 6); //6 is the level of compression ("aggression")

    datasetId = H5Dcreate2(fileId, dSetName, H5T_IEEE_F64BE, dataspaceId, H5P_DEFAULT, plistId, H5P_DEFAULT);

    statusFileInFunction = H5Dwrite(datasetId, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInFunction = H5Sclose(dataspaceId);
    statusFileInFunction = H5Dclose(datasetId);
    statusFileInFunction = H5Pclose(plistId);


}

void HDF5Writer::writeChunckedSZIP(double* dataBase, int size, const char* dSetName) 
{


    herr_t statusFileInFunction;
    hid_t datasetId;
    hid_t dataspaceId;
    hsize_t dims[1];
    hsize_t cdims[1];

    hid_t plistId;

    size_t nelmts;
    unsigned flags;
    unsigned filterInfo;
    H5Z_filter_t filterType;

    unsigned szip_options_mask;
    unsigned szip_pixels_per_block;

    dims[0] = size;
    cdims[0] = size;

    int i, j, numfilt;

    // char newDSetName[85] = "Compressed_";
    // strcat(newDSetName,dSetName);


    dataspaceId = H5Screate_simple(1, dims, NULL);

    plistId = H5Pcreate(H5P_DATASET_CREATE);

    statusFileInFunction = H5Pset_chunk(plistId, 1, cdims);

    szip_options_mask = H5_SZIP_NN_OPTION_MASK;
    szip_pixels_per_block = 16;
    statusFileInFunction = H5Pset_szip(plistId, szip_options_mask, szip_pixels_per_block);

    datasetId = H5Dcreate2(fileId, dSetName, H5T_IEEE_F64BE, dataspaceId, H5P_DEFAULT, plistId, H5P_DEFAULT);

    statusFileInFunction = H5Dwrite(datasetId, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInFunction = H5Sclose(dataspaceId);
    statusFileInFunction = H5Dclose(datasetId);
    statusFileInFunction = H5Pclose(plistId);


}

void HDF5Writer::writeChunckedZLIB(double* dataBase, int size, const char* dSetName) 
{


    herr_t statusFileInFunction;
    hid_t datasetId;
    hid_t dataspaceId;
    hsize_t dims[1];
    hsize_t cdims[1];

    hid_t plistId;

    size_t nelmts;
    unsigned flags;
    unsigned filterInfo;
    H5Z_filter_t filterType;

    dims[0] = size;
    cdims[0] = size;


    int i, j, numfilt;

    // char newDSetName[85] = "Compressed_";
    // strcat(newDSetName,dSetName);


    dataspaceId = H5Screate_simple(1, dims, NULL);

    plistId = H5Pcreate(H5P_DATASET_CREATE);

    statusFileInFunction = H5Pset_chunk(plistId, 1, cdims);
    statusFileInFunction = H5Pset_deflate(plistId, 6); //6 is the level of compression ("aggression")

    datasetId = H5Dcreate2(fileId, dSetName, H5T_IEEE_F64BE, dataspaceId, H5P_DEFAULT, plistId, H5P_DEFAULT);

    statusFileInFunction = H5Dwrite(datasetId, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);

    statusFileInFunction = H5Sclose(dataspaceId);
    statusFileInFunction = H5Dclose(datasetId);
    statusFileInFunction = H5Pclose(plistId);


}