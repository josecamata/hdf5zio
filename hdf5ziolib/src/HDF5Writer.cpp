#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
#include <GetPotGuard.hpp>

using namespace std;

#include "config.h"
#include "HDF5Writer.h"

HDF5Writer::HDF5Writer(const char* fileName)
: HDF5Base(fileName) 
{
    this->readConfigFile();
    fileId = H5Fcreate(fileName, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
}

void HDF5Writer::readConfigFile() {

    // Find config file
    std::ofstream configFile;
    std::string config_file = CONFIG_DIR + std::string("config.pot");
    configFile.open(config_file, std::ios::app);
    if (!configFile.is_open()) {
        std::cerr << "\nCreating default config file . . .\n";
        std::cerr << config_file << std::endl;
        // TODO : Implementar criação de arquivo config
        std::cerr << "\nNot yet implemented\n";
    }
    configFile.close();

    GetPot ifile(config_file);

    int ct = ifile("compression_type", 0);
    this->c = (CompressionType) ct;

    if (this->c == ZFP) { // ZFP
        this->zfp_mode = ifile("zfp_mode", 5);

        if (this->zfp_mode == 2) { // zfp mode precision
            this->zfp_prec = ifile("zfp_precision", 5);
        }

        
    }

    //H5Z_zfp_initialize();
}

HDF5Writer::~HDF5Writer() {
   // H5Z_zfp_finalize();
    H5Fclose(fileId);
}

std::string HDF5Writer::getCompression() {
    switch (this->c)
    {
        case ZLIB:
            return "ZLIB";
        case SZIP:
            return "SZIP";
        case ZFP:
            return "ZFP";
        default:
            return "NO_COMPRESSION";
    }
}

void HDF5Writer::write(int* dataBase, int size, const char* dSetName)
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
        writeChunckedZFP(dataBase, size, dSetName);
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
        writeChunckedZLIB(dataBase, size, dSetName);
        break;
    case SZIP:
        writeChunckedSZIP(dataBase, size, dSetName);
        break;
    case ZFP:
        writeChunckedZFP(dataBase, size, dSetName);
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
    case ZFP:
        writeChunckedZFP(dataBase, size, dSetName);
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

    // char dSetName[85] = "Compressed_";
    // strcat(dSetName,dSetName);

    

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

    // char dSetName[85] = "Compressed_";
    // strcat(dSetName,dSetName);

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

    // char dSetName[85] = "Compressed_";
    // strcat(dSetName,dSetName);

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

    // char dSetName[85] = "Compressed_";
    // strcat(dSetName,dSetName);

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

    // char dSetName[85] = "Compressed_";
    // strcat(dSetName,dSetName);


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

    // char dSetName[85] = "Compressed_";
    // strcat(dSetName,dSetName);


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

void HDF5Writer::writeChunckedZFP(int* dataBase, int size, const char* dSetName)
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

    unsigned int cd_values[10];
    size_t cd_nelmts = 10;

    if (this->zfp_mode == H5Z_ZFP_MODE_REVERSIBLE) {
        H5Pset_zfp_reversible_cdata(cd_nelmts, cd_values); // num_elements ??? values ???
    } else if (this->zfp_mode == H5Z_ZFP_MODE_PRECISION) {
        H5Pset_zfp_precision_cdata(this->zfp_prec, cd_nelmts, cd_values);
    } else {
        std::cerr << "\nInvalid ZFP_MODE type\n";
        return;
    }

    H5Pset_filter(plistId, H5Z_FILTER_ZFP, H5Z_FLAG_MANDATORY, cd_nelmts, cd_values);

    dataspaceId = H5Screate_simple(1, dims, 0);

    datasetId = H5Dcreate2(fileId, dSetName, H5T_NATIVE_INT, dataspaceId, H5P_DEFAULT, plistId, H5P_DEFAULT);
    statusFileInFunction = H5Dwrite(datasetId, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);
    statusFileInFunction = H5Dclose(datasetId);

    

    statusFileInFunction = H5Sclose(dataspaceId);
    statusFileInFunction = H5Pclose(plistId);
}

void HDF5Writer::writeChunckedZFP(float* dataBase, int size, const char* dSetName)
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

    unsigned cd_values[10];
    size_t cd_nelmts = 10;

    if (this->zfp_mode == H5Z_ZFP_MODE_REVERSIBLE) {
        H5Pset_zfp_reversible_cdata(cd_nelmts, cd_values); // num_elements ??? values ???
    } else if (this->zfp_mode == H5Z_ZFP_MODE_PRECISION) {
        H5Pset_zfp_precision_cdata(this->zfp_prec, cd_nelmts, cd_values);
    } else {
        std::cerr << "\nInvalid ZFP_MODE type\n";
        return;
    }

    H5Pset_filter(plistId, H5Z_FILTER_ZFP, H5Z_FLAG_MANDATORY, cd_nelmts, cd_values);

    dataspaceId = H5Screate_simple(1, dims, 0);

    datasetId = H5Dcreate2(fileId, dSetName, H5T_NATIVE_FLOAT, dataspaceId, H5P_DEFAULT, plistId, H5P_DEFAULT);
    statusFileInFunction = H5Dwrite(datasetId, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);
    statusFileInFunction = H5Dclose(datasetId);

    //H5Z_zfp_finalize();

    statusFileInFunction = H5Sclose(dataspaceId);
    statusFileInFunction = H5Pclose(plistId);
}

void HDF5Writer::writeChunckedZFP(double* dataBase, int size, const char* dSetName) 
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

    unsigned cd_values[10];
    size_t cd_nelmts = 10;

    if (this->zfp_mode == H5Z_ZFP_MODE_REVERSIBLE) {
        H5Pset_zfp_reversible_cdata(cd_nelmts, cd_values); // num_elements ??? values ???
    } else if (this->zfp_mode == H5Z_ZFP_MODE_PRECISION) {
        H5Pset_zfp_precision_cdata(this->zfp_prec, cd_nelmts, cd_values);
    } else {
        std::cerr << "\nInvalid ZFP_MODE type\n";
        return;
    }

    H5Pset_filter(plistId, H5Z_FILTER_ZFP, H5Z_FLAG_MANDATORY, cd_nelmts, cd_values);

    dataspaceId = H5Screate_simple(1, dims, 0);

    datasetId = H5Dcreate2(fileId, dSetName, H5T_NATIVE_DOUBLE, dataspaceId, H5P_DEFAULT, plistId, H5P_DEFAULT);
    statusFileInFunction = H5Dwrite(datasetId, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, dataBase);
    statusFileInFunction = H5Dclose(datasetId);


    statusFileInFunction = H5Sclose(dataspaceId);
    statusFileInFunction = H5Pclose(plistId);
}
