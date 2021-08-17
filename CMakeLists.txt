cmake_minimum_required(VERSION 3.10)

project(testeHDF5)
file(GLOB source_files
            "*.h"
            "*.cpp"
            "src/*.cpp"
            "include/*.h"
    )
add_executable(tpProgram.exe ${source_files})

find_package(HDF5 REQUIRED)
find_package(MPI)
include_directories(./include)
if(HDF5_FOUND)
    include_directories(${HDF5_INCLUDE_DIRS})
    target_link_libraries(tpProgram.exe PUBLIC ${HDF5_C_LIBRARIES}) 
endif()
