#ifndef F6158211_B632_4B28_83EE_11AA2B5C8C52
#define F6158211_B632_4B28_83EE_11AA2B5C8C52

#include "H5Cpp.h"

class HDF5Base{
    public:
        HDF5Base(char* fileName);
        void close();
    protected:
        char fileName[50];
        hid_t fileId;
        int numOfDimensions;
        void setNumberOfDimensions(int numberOfDimensions);
    private:
};

#endif /* F6158211_B632_4B28_83EE_11AA2B5C8C52 */
