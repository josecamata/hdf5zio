
file(GLOB source_files
            "src/*.cpp"
            "include/*.h"
    )
    
add_library(HDF5zio ${source_files})
include_directories(./include)

