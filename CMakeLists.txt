cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0057 NEW)
set(CMAKE_CXX_STANDARD 14)

project(hdf5zio)

find_package(HDF5 REQUIRED)
find_package(MPI)

if(HDF5_FOUND)
include_directories(${HDF5_INCLUDE_DIRS})
endif()

include_directories(${CMAKE_SOURCE_DIR}/hdf5ziolib/include)

# Build the library
add_subdirectory(hdf5ziolib)
add_subdirectory(tests)
#add_executable(HDF5zio-test tests/main.cpp)
#target_link_libraries(HDF5zio-test PUBLIC HDF5zio ${HDF5_C_LIBRARIES})




