
#ifndef HDF5READER_H
#define HDF5READER_H

#include "HDF5Base.h"



class HDF5Reader: public HDF5Base{
    public:
        bool isChuncked;
        HDF5Reader(const char* fileName);
        void read(int* dataBase, int size, const char* dSetName);
        void read(float* dataBase, int size, const char* dSetName);
        void read(double* dataBase, int size, const char* dSetName);
    
    private:
        void readNormal(int* dataBase, int size, const char* dSetName);
        void readNormal(float* dataBase, int size, const char* dSetName);
        void readNormal(double* dataBase, int size, const char* dSetName);
        void readChuncked(double* dataBase, int size, const char* dSetName);
        void readChuncked(int* dataBase, int size, const char* dSetName);
        void readChuncked(float* dataBase, int size, const char* dSetName);
};

#endif /* HDF5READER_H */