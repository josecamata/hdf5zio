
add_executable(write_test write_test.cpp)
add_executable(read_test read_test.cpp)
add_executable(xdmf_test xdmf_test.cpp)
add_executable(hurricane hurricane.cpp)


include_directories(${HDF5_INCLUDE_DIRS})

target_link_libraries(write_test PUBLIC HDF5zio ${HDF5_C_LIBRARIES})
target_link_libraries(read_test PUBLIC HDF5zio ${HDF5_C_LIBRARIES})
target_link_libraries(xdmf_test PUBLIC HDF5zio ${HDF5_C_LIBRARIES})

target_link_libraries(hurricane PUBLIC HDF5zio ${HDF5_C_LIBRARIES})

