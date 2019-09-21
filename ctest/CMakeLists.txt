cmake_minimum_required(VERSION 3.0)
project (ctest_ex1) 
#
set(CMAKE_VERBOSE_MAKEFILE ON)
set(GTEST_HOME  /home/hpjeon/sw_local/gtest)
include_directories(${GTEST_HOME}/include)
link_directories(${GTEST_HOME}/lib)
add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -g -Wall")

set(source1 test1.cpp)
set(source2 test2.cpp)
set(mainsource main.cpp sub.cpp)
add_executable(a.exe ${mainsource})
add_executable(test1 ${source1})
add_executable(test2 ${source2})
target_link_libraries(test1 gtest pthread)
target_link_libraries(test2 gtest pthread)

enable_testing()
add_test(NAME test1 COMMAND test1)
add_test(NAME test2 COMMAND test2)

