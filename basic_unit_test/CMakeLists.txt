project(mdbasic)
cmake_minimum_required(VERSION 2.6)

include_directories($ENV{GMOCK_HOME}/include $ENV{GMOCK_HOME}/gtest/include)
link_directories($ENV{GMOCK_HOME}/lib $ENV{GMOCK_HOME}/gtest/mybuild)
add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

set(sources 
   main.cpp 
   test.cpp)
add_executable(unittest ${sources})
target_link_libraries(unittest gmock gtest pthread)

