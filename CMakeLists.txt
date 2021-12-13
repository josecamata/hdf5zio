cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0057 NEW)
set(CMAKE_CXX_STANDARD 14)

find_package(HDF5 REQUIRED COMPONENTS C HL)
find_package(MPI)

include_directories(${CMAKE_SOURCE_DIR}/hdf5ziolib/include)

# Build the library
add_subdirectory(hdf5ziolib)
add_subdirectory(tests)


