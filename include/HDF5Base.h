#ifndef F6158211_B632_4B28_83EE_11AA2B5C8C52
#define F6158211_B632_4B28_83EE_11AA2B5C8C52

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

#endif /* F6158211_B632_4B28_83EE_11AA2B5C8C52 */
