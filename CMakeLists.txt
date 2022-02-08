cmake_minimum_required(VERSION 3.10)

project(HDF5zio)
file(GLOB source_files
            "src/*.cpp"
            "include/*.h"
    )
    
add_library(HDF5zio ${source_files})

# Variavel de ambiente HDF5_DIR ou HDF5_ROOT devem ser definidas
find_package(HDF5 REQUIRED)
find_package(MPI)
include_directories(./include)
if(HDF5_FOUND)
    include_directories(${HDF5_INCLUDE_DIRS})
    #target_link_libraries(HDF5zio.exe PUBLIC ${HDF5_C_LIBRARIES}) 
endif()
