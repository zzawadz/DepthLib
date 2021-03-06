cmake_minimum_required (VERSION 3.0.2)
project (DepthLib CXX)

# Armadillo library
find_library(Armadillo REQUIRED)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0")

# The version number.
set (DepthLib_VERSION_MAJOR 0)
set (DepthLib_VERSION_MINOR 1)

option(BUILD_SHARED_LIBS "Build shared library" ON)

configure_file(
  "${PROJECT_SOURCE_DIR}/DepthLibConfig.h.in"
  "${PROJECT_BINARY_DIR}/DepthLibConfig.h"
 )

add_library(DepthLib 
  library/algorithm/distance_depths.cpp 
  library/algorithm/functional_depths.cpp
  library/algorithm/standard_depths.cpp
  library/algorithm/local_depth.cpp 
  library/algorithm/depth.cpp
 )
 

  
 
option(BUILD_SHARED_LIBS "Build shared library" ON)
 
#SET_TARGET_PROPERTIES(DepthLib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(DepthLib armadillo)

add_subdirectory(Examples)

add_test(MahalanobisDepth Examples/distance_depths_test)
add_test(MahalanobisDepth Examples/functional_depths_test)