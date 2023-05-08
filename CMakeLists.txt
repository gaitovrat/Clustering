cmake_minimum_required(VERSION 3.0)
project(pds)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/common)
include_directories(${common_INC})
link_libraries(${common_LIB})

add_subdirectory(${PROJECT_SOURCE_DIR}/src/parallel)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/sequential)
