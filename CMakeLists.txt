cmake_minimum_required(VERSION 3.10)

project(HDF5zio)
file(GLOB source_files
            "*.h"
            "*.cpp"
            "src/*.cpp"
            "include/*.h"
    )
add_executable(HDF5zio.exe ${source_files})

find_package(HDF5 REQUIRED)
find_package(MPI)
include_directories(./include)
include_directories(/opt/lib/h5z_zfp/include)
if(HDF5_FOUND)
    include_directories(${HDF5_INCLUDE_DIRS})
    target_link_libraries(HDF5zio.exe PUBLIC ${HDF5_C_LIBRARIES} /opt/lib/h5z_zfp/lib/libh5zzfp.a /opt/lib/h5z_zfp/plugin/libh5zzfp.so) 
endif()
