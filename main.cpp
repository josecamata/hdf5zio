#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
#include "HDF5Writer.h"
#include "HDF5Reader.h"
//#include "HDF5Reader.h"

using namespace std;

int main(void){

    char name0[] = "testNC.h5";
    char name1[] = "testSZIP.h5";
    char name2[] = "testZLIB.h5";
    int tam = 1000;

    int *database = new int[tam];

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
    myFile1.setCompression(SZIP);

    myFile1.write(database, tam, "Compression Test");

    myFile1.close();

/**************************************************************/

    HDF5Writer myFile2(name2);
    myFile2.setCompression(ZLIB);

    myFile2.write(database, tam, "Compression Test");

    HDF5Reader myFile("testSZIP.h5");
    int *databas = new int[tam];
    myFile.read("testSZIP.h5", databas, tam, "Compression Test");

/***************************************************************/
    cout<<"Finished"<<endl;

    HDF5Reader myFile("testSZIP.h5");
    int *databas = new int[tam];
    myFile.read("testSZIP.h5", databas, tam, "Compression Test");

    return 0;
}
