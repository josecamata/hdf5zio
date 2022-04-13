#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
#include <chrono>
#include <fstream>

#include "HDF5Writer.h"

void geracao2(float* vect, int size){
    float r;

    for(int i = 0; i < size; i++){
        r = -0.25 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(800-(-0.25))));
        vect[i] = r;
    }
}

void zfp_test_prec(){

    char zfpFileName[] = "zfp_test_prec.h5";

    int size = 1000000;

    //int *database = new int[size];
    std::unique_ptr<float> database(new float[size]);

    geracao2(database.get(), size);
    
    HDF5Writer zfpFile(zfpFileName);
    
    zfpFile.write(database.get(), size, "test_prec");
    zfpFile.close();
}