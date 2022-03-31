
add_executable(HDF5zio-test main.cpp)

include_directories(${HDF5_INCLUDE_DIRS})
target_link_libraries(HDF5zio-test PUBLIC HDF5zio ${HDF5_C_LIBRARIES})
