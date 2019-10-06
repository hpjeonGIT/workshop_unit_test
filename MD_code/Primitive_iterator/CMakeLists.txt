#
# Cmake example with unit-test
# ref: https://crascit.com/2015/07/25/cmake-gtest/
# ref: https://github.com/kaizouman/gtest-cmake-example
cmake_minimum_required(VERSION 3.0)
#
project(MD_class)
set(CMAKE_VERBOSE_MAKEFILE ON)
add_definitions(-std=c++14)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -g -Wall")
enable_testing()
#
add_subdirectory(src)
add_subdirectory(test)
