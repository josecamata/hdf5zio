#ifndef C818BBCA_66C0_4F0E_8BC0_F207B9B4878C
#define C818BBCA_66C0_4F0E_8BC0_F207B9B4878C

#include "HDF5Base.h"

class HDF5Writer: public HDF5Base{
    public:
        HDF5Writer(const char* fileName, bool isChuncked);
        void writeHDF5();
        void write(int* dataBase, int size, const char* dSetName);
        void write(float* dataBase, int size, const char* dSetName);
    private:
        bool isChuncked;
        //Write functions:
        void writeNormal(int* dataBase, int size, const char* dSetName); //Write a integer database
        void writeNormal(float* dataBase, int size, const char* dSetName); //Write a float database
        void writeNormal(double* dataBase, int size, const char* dSetName); //Write a double database
        
        void writeChuncked(int* dataBase, int size, const char* dSetName);
};

#endif /* C818BBCA_66C0_4F0E_8BC0_F207B9B4878C */
