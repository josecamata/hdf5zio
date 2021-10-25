#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
#include "H5Cpp.h"
#include "HDF5Writer.h"
#include "HDF5Reader.h"

using namespace std;

int main(void){
    char name[] = "testZLIB.h5";
    int tam = 4096;

    float database[tam];

    for(int i = 0; i < tam; i++){
        database[i] = i + 2 * 5 - 4;
    }

    HDF5Writer myFile(name);
    myFile.setCompression(ZLIB);

    myFile.write(database, tam, "Compression Test");

    myFile.close();

    cout<<"Finished"<<endl;
    return 0;
}
