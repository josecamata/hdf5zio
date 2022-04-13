#ifndef C818BBCA_66C0_4F0E_8BC0_F207B9B4878C
#define C818BBCA_66C0_4F0E_8BC0_F207B9B4878C

#include "HDF5Base.h"

typedef enum{NOCOMPRESSION = 0, SZIP, ZLIB, ZFP}CompressionType;

class HDF5Writer: public HDF5Base{
    public:
        HDF5Writer(const char* fileName);
        void writeHDF5();
        void write(int* dataBase, int size, const char* dSetName);
        void write(float* dataBase, int size, const char* dSetName);
        void write(double* dataBase, int size, const char* dSetName);
        void setCompression(CompressionType c);
    private:
        CompressionType c;

        int zfp_mode;
        uint zfp_prec;
        //Write functions:
        void writeNormal(int* dataBase, int size, const char* dSetName); //Write a integer database
        void writeNormal(float* dataBase, int size, const char* dSetName); //Write a float database
        void writeNormal(double* dataBase, int size, const char* dSetName); //Write a double database
        
        void writeChunckedSZIP(int* dataBase, int size, const char* dSetName);
        void writeChunckedZLIB(int* dataBase, int size, const char* dSetName);
        void writeChunckedZFP (int* dataBase, int size, const char* dSetName);
        void writeChunckedSZIP(float* dataBase, int size, const char* dSetName);
        void writeChunckedZLIB(float* dataBase, int size, const char* dSetName);
        void writeChunckedZFP (float* dataBase, int size, const char* dSetName);
        void writeChunckedSZIP(double* dataBase, int size, const char* dSetName);
        void writeChunckedZLIB(double* dataBase, int size, const char* dSetName);
        void writeChunckedZFP (double* dataBase, int size, const char* dSetName);

        void readConfigFile();
};

#endif /* C818BBCA_66C0_4F0E_8BC0_F207B9B4878C */
