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
    int tam = 7;

    int database[tam];

    for(int i = 0; i < tam; i++){
        cin>>database[i];
        cout<<endl;
    }

    HDF5Writer myFile(name, false);

    myFile.write(database, tam, "hdyhdygd");

    myFile.close();

    return 0;
}