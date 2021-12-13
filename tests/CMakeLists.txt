
project(HDF5zio-tests)
file(GLOB source_files
            "*.cpp"
            "*.h"
    )
    
add_executable(HDF5zio-tests ${source_files})

include_directories(${HDF5_INCLUDE_DIRS})
target_link_libraries(HDF5zio-tests PRIVATE hdf5 HDF5zio)

