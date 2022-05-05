cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0057 NEW)
cmake_policy(SET CMP0028 NEW) 
set(CMAKE_CXX_STANDARD 14)

project(hdf5zio)

find_package(HDF5 REQUIRED)
find_package(MPI)
find_package(ZFP)

include(CheckFortranCompilerFlag)

option(USE_ZFP "Use ZFP compression" ON)


if(HDF5_FOUND)
  include_directories(${HDF5_INCLUDE_DIRS})
endif()

if(ZFP_FOUND)
  if(H5Z_ZFP_DIR)
    include_directories(${H5Z_ZFP_DIR}/include)
   else()
    message(FATAL_ERROR "H5Z_ZFP_DIR not set")
   endif()
    include_directories(${ZFP_INCLUDE_DIRS})
endif()

include_directories(${CMAKE_SOURCE_DIR}/hdf5ziolib/include)

# Build the library
add_subdirectory(hdf5ziolib)
add_subdirectory(tests)





