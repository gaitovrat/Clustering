cmake_minimum_required(VERSION 3.0)
project(pds)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/common)
include_directories(${common_INC})
link_libraries(${common_LIB})

add_subdirectory(${PROJECT_SOURCE_DIR}/src/parallel)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/sequential)
