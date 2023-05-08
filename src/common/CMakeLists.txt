add_library(${PROJECT_NAME}-common Point.cpp)

set(common_INC ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
set(common_LIB ${PROJECT_NAME}-common PARENT_SCOPE)
