cmake_minimum_required(VERSION 3.10)

project(HDF5zio-tests)
file(GLOB source_files
            "*.cpp"
            "*.h"
    )
    
add_executable(HDF5zio-tests ${source_files})

find_package(HDF5 REQUIRED)
find_package(HDF5zio REQUIRED)
find_package(MPI)
include_directories(./include)

if(HDF5_FOUND)
    include_directories(${HDF5_INCLUDE_DIRS})
    target_link_libraries(HDF5zio-tests PUBLIC ${HDF5_C_LIBRARIES} HDF5zio) 
    
endif()
