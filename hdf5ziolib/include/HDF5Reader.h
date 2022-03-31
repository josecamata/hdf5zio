#ifndef HDF5READER_H
#define HDF5READER_H

#include "HDF5Base.h"



class HDF5Reader: public HDF5Base{
    public:
        bool isChuncked;
        HDF5Reader(const char* fileName);
        void read(const char *name, int* dataBase, int size, const char* dSetName);
        void read(const char *name, float* dataBase, int size, const char* dSetName);
        void read(const char *name, double* dataBase, int size, const char* dSetName);
    
    private:
        void readNormal(const char* name, int* dataBase, int size, const char* dSetName);
        void readNormal(const char* name, float* dataBase, int size, const char* dSetName);
        void readNormal(const char* name, double* dataBase, int size, const char* dSetName);
        void readChuncked(const char* name, double* dataBase, int size, const char* dSetName);
        void readChuncked(const char* name, int* dataBase, int size, const char* dSetName);
        void readChuncked(const char* name, float* dataBase, int size, const char* dSetName);
};

#endif /* HDF5READER_H */
