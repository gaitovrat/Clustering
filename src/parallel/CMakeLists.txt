find_package(OpenMP REQUIRED)
find_package(OpenCL REQUIRED)

add_executable(${PROJECT_NAME}-parallel parallel.cpp SolutionParallel.cpp OpenCLContext.cpp)

target_link_libraries(${PROJECT_NAME}-parallel PRIVATE OpenMP::OpenMP_CXX OpenCL::OpenCL)
