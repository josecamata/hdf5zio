#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
#include <chrono>
#include <fstream>

#include "HDF5Writer.h"

void geracao(float* vect, int size){
    float r;

    for(int i = 0; i < size; i++){
        r = -0.25 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(800-(-0.25))));
        vect[i] = r;
    }
}

void zfp_test(){

    char zfpFileName[] = "zfp_test.h5";

    int size = 1000000;

    //int *database = new int[size];
    std::unique_ptr<float> database(new float[size]);

    geracao(database.get(), size);
    
    HDF5Writer zfpFile(zfpFileName);
    zfpFile.setCompression(ZFP);
    
    zfpFile.write(database.get(), size, "test");
    zfpFile.close();
}