#ifndef HDF5BASE_H
#define HDF5BASE_H

#include "hdf5.h"

#include "H5Zzfp_lib.h"
#include "H5Zzfp_props.h"

class HDF5Base{
    public:
        HDF5Base(const char* fileName);
        void close();
    protected:
        char fileName[50];
        hid_t fileId;
    private:
};

#endif /* HDF5BASE_H */
