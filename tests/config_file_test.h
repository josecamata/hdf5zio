#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
#include <chrono>
#include <fstream>

#include "HDF5Writer.h"

void geracaoConfig(float* vect, int size){
    float r;

    for(int i = 0; i < size; i++){
        r = -0.25 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(800-(-0.25))));
        vect[i] = r;
    }
}

void config_file_test(){

    char zfpFileName[] = "test_config.h5";

    int size = 1000000;

    //int *database = new int[size];
    std::unique_ptr<float> database(new float[size]);

    geracaoConfig(database.get(), size);
    
    HDF5Writer zfpFile(zfpFileName);
    
    zfpFile.write(database.get(), size, "test_config");
    zfpFile.close();

    std::cout << "Compression Type: " << zfpFile.compression() << "\n";
    std::cout << "ZFP MODE: " << zfpFile.zfpmode() << "\n";
    std::cout << "ZFP PRECISION: " << zfpFile.zfpprec() << "\n";
}