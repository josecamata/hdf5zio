#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

#include "HDF5Base.h"

HDF5Base::HDF5Base(char* fileName) 
{
    strcpy(this->fileName, fileName);

}

void HDF5Base::close() 
{
    H5Fclose(fileId);
}

void HDF5Base::setNumberOfDimensions(int numberOfDimensions) 
{
    this->numOfDimensions = numberOfDimensions;
}
