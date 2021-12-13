#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
#include "HDF5Writer.h"
//#include "HDF5Reader.h"

using namespace std;

int main(void){

    char name0[] = "testNC.h5";
    char name1[] = "testSZIP.h5";
    char name2[] = "testZLIB.h5";
    int tam = 100000000;

    float *database = new float[tam];

    for(int i = 0; i < tam; i++){
        database[i] = i + 2 * 5 - 4;
    }
/**************************************************************/

    HDF5Writer myFile0(name0);
    myFile0.setCompression(NOCOMPRESSION);

    myFile0.write(database, tam, "Compression Test");

    myFile0.close();

/**************************************************************/

    HDF5Writer myFile1(name1);
    myFile1.setCompression(ZLIB);

    myFile1.write(database, tam, "Compression Test");

    myFile1.close();

/**************************************************************/

    HDF5Writer myFile2(name2);
    myFile2.setCompression(ZLIB);

    myFile2.write(database, tam, "Compression Test");

    myFile2.close();

/***************************************************************/
    cout<<"Finished"<<endl;
    return 0;
}
