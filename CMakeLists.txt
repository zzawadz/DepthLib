cmake_minimum_required (VERSION 2.6)
project (DepthLib CXX)

# Armadillo library
find_library(Armadillo REQUIRED)


# The version number.
set (DepthLib_VERSION_MAJOR 0)
set (DepthLib_VERSION_MINOR 1)

option(BUILD_SHARED_LIBS "Build shared library" ON)

configure_file(
  "${PROJECT_SOURCE_DIR}/DepthLibConfig.h.in"
  "${PROJECT_BINARY_DIR}/DepthLibConfig.h"
 )

add_library(DepthLib library/algorithm/euclid_depth.cpp library/algorithm/mb_depth.cpp)
 
option(BUILD_SHARED_LIBS "Build shared library" ON)
 
#SET_TARGET_PROPERTIES(DepthLib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(DepthLib armadillo)