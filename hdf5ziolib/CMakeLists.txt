

file(GLOB source_files
            "src/*.cpp"
            "include/*.h"
    )
    

    
add_library(HDF5zio ${source_files})


include_directories(./include)
if(HDF5_FOUND)
    include_directories(${HDF5_INCLUDE_DIRS})
endif()
