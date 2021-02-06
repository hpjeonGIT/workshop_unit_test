project(denseSolver CXX CUDA)
cmake_minimum_required(VERSION 2.6)

add_definitions(-std=c++14)
find_package(CUDA REQUIRED)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")
enable_testing()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2")
add_subdirectory(main)
add_subdirectory(regression_test)
# Ref: https://stackoverflow.com/questions/6352123/multiple-directories-under-cmake
#https://gitlab.com/CLIUtils/modern-cmake/tree/master/examples/extended-project
