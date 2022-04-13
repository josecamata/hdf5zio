#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
#include <chrono>
#include <fstream>

#include "HDF5Writer.h"

void geracao3(float* vect, int size){
    float r;

    for(int i = 0; i < size; i++){
        r = -0.25 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(800-(-0.25))));
        vect[i] = r;
    }
}

void comp_test(){

    char zfpFileName[] = "zfp_test_2.h5";
    char noCompFileName[] = "noComp_test_2.h5";

    int size = 1000000;

    //int *database = new int[size];
    std::unique_ptr<float> database(new float[size]);

    geracao3(database.get(), size);
    
    HDF5Writer zfpFile(zfpFileName);
    
    zfpFile.write(database.get(), size, "test_prec");
    zfpFile.close();

    std::cout << "Compression Type: " << zfpFile.compression() << "\n";
    std::cout << "ZFP MODE: " << zfpFile.zfpmode() << "\n";
    std::cout << "ZFP PRECISION: " << zfpFile.zfpprec() << "\n";

    HDF5Writer noCompFile(noCompFileName);
    
    noCompFile.setCompression(NOCOMPRESSION);
    noCompFile.write(database.get(), size, "test_prec");
    noCompFile.close();

    std::cout << "Compression Type: " << noCompFile.compression() << "\n";

    HDF5Reader leitorNoComp(noCompFileName);

    float* obuf;
    noCompFile.readNormal(noCompFileName, obuf, size, "test_prec");

    float* cbuf;
    zfpFile.readZFP(zfpFileName, cbuf, size, "test_prec");

    double max_absdiff = 0;
    double max_reldiff = 0;
    
    double actual_max_absdiff = 0;
    double actual_max_reldiff = 0;
    int num_absdiffs = 0;
    int num_reldiffs = 0;

    for (size_t i = 0; i < size; i++)
    {
        double absdiff = obuf[i] - cbuf[i];
        if (absdiff < 0) absdiff = -absdiff;
        if (absdiff > 0)
        {
            double reldiff = 0;
            if (obuf[i] != 0) reldiff = absdiff / obuf[i];

            if (absdiff > actual_max_absdiff) actual_max_absdiff = absdiff;
            if (reldiff > actual_max_reldiff) actual_max_reldiff = reldiff;
            if (absdiff > max_absdiff)
                num_absdiffs++;
            if (reldiff > max_reldiff)
                num_reldiffs++;
        }
    }

    printf("Absolute Diffs: %d values are different; actual-max-absdiff = %g\n",
        num_absdiffs, actual_max_absdiff);
    printf("Relative Diffs: %d values are different; actual-max-reldiff = %g\n",
        num_reldiffs, actual_max_reldiff);
}