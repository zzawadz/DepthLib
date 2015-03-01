cmake_minimum_required (VERSION 2.6)
project (Example CXX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0")

#find_library(Armadillo REQUIRED)
#add_library(DepthLib SHARED IMPORTED)
#set_target_properties(DepthLib PROPERTIES IMPORTED_LOCATION ${DEPTHLIB_PATH})

include_directories(../)
add_executable(distance_depths_test src/distance_depths_test.cpp)

#SET_TARGET_PROPERTIES(DepthLib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(distance_depths_test DepthLib armadillo)

