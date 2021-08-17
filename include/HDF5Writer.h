#ifndef C818BBCA_66C0_4F0E_8BC0_F207B9B4878C
#define C818BBCA_66C0_4F0E_8BC0_F207B9B4878C

#include "HDF5Base.h"

class HDF5Writer: public HDF5Base{
    public:
        HDF5Writer(char* fileName, int numberOfDimensions);
        HDF5Writer(char* fileName, bool isChuncked);
        void writeHDF5();
        void write();
    private:
        bool isChuncked;
        void writeNormal();
        void writeChuncked();
};

#endif /* C818BBCA_66C0_4F0E_8BC0_F207B9B4878C */
