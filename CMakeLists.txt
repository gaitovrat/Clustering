cmake_minimum_required(VERSION 3.0)
project(pds)

include_directories(${PROJECT_SOURCE_DIR}/src/common)

include(${PROJECT_SOURCE_DIR}/src/parallel/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/src/sequential/CMakeLists.txt)
