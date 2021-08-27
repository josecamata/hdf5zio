#ifndef CC1753F2_12F5_4673_AC11_5E0420BE3D5E
#define CC1753F2_12F5_4673_AC11_5E0420BE3D5E

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
        void readChuncked(const char* name);
};

#endif /* CC1753F2_12F5_4673_AC11_5E0420BE3D5E */
