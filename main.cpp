#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
#include "H5Cpp.h"
#include "HDF5Writer.h"

using namespace std;
int main(void){
    char name[] = "test.h5";
    int di = 3;
    HDF5Writer myFile(name, di);

    myFile.writeHDF5();

    myFile.close();

    return 0;
}