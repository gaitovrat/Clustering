add_executable(${PROJECT_NAME}-parallel  ${CMAKE_CURRENT_LIST_DIR}/parallel.cpp)
target_include_directories(${PROJECT_NAME}-parallel PRIVATE ${CMAKE_CURRENT_LIST_DIR})
