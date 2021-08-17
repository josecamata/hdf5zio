#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

#include "HDF5Writer.h"

HDF5Writer::HDF5Writer(char* fileName, int numberOfDimensions) 
: HDF5Base(fileName)
{
    fileId = H5Fcreate(fileName, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    setNumberOfDimensions(numberOfDimensions);
}

void HDF5Writer::writeHDF5() 
{
    bool answer;
    cout<<"This file must be chunked? \n(0--> No\n1-->Yes)"<<endl;
    cin>>answer;
    cout<<endl;

    if(answer){
        writeChuncked();
    }
    else if(!answer){
        writeNormal();
    }
}

void HDF5Writer::writeNormal() 
{
    herr_t statusFileInTheFunction;
    hsize_t dims[numOfDimensions];
    hid_t datasetId;
    hid_t dataspaceId;
    int account = 1;

    for (int i = 0; i < numOfDimensions; i++)
    {
        cout<<"["<<i<<"] = ";
        cin>>dims[i];
    }

    for (int j = 0; j < numOfDimensions-1; j++)
    {
        account += dims[j] * dims[j+1];
    }

    dataspaceId = H5Screate_simple(numOfDimensions, dims, NULL);

    datasetId = H5Dcreate2(fileId, "/dset", H5T_STD_I32BE, dataspaceId, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    float dsetData[account]; 

    for (int i = 0; i < account; i++)
    {
        cout<<"["<<i<<"] = ";
        cin>>dsetData[i];
        cout<<", ";
    }

    statusFileInTheFunction = H5Dwrite(datasetId, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dsetData);

    /*End acces to the dataset and release resources used by it*/
    statusFileInTheFunction = H5Dclose(datasetId);

    /*Terminate access to the data space*/
    statusFileInTheFunction = H5Sclose(dataspaceId);


}

void HDF5Writer::writeChuncked() 
{
    cout<<"Em manutenção"<<endl;
}



