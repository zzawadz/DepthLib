cmake_minimum_required (VERSION 2.6)
project (Example CXX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0")

add_library(DepthLib SHARED IMPORTED)
set_target_properties(DepthLib PROPERTIES IMPORTED_LOCATION ${DEPTHLIB_PATH})

include_directories(/home/zzawadz/GithubRepos/DepthLib)
add_executable(euclid_test src/euclid_test.cpp)
add_executable(mah_test src/mah_test.cpp)

 
#SET_TARGET_PROPERTIES(DepthLib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(euclid_test DepthLib)
target_link_libraries(mah_test DepthLib)