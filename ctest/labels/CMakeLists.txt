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
set(source3 test3.cpp)
set(source4 test4.cpp)
set(mainsource main.cpp sub.cpp)
add_executable(a.exe ${mainsource})
add_executable(test1 ${source1})
add_executable(test2 ${source2})
add_executable(test3 ${source3})
add_executable(test4 ${source4})
target_link_libraries(test1 gtest pthread)
target_link_libraries(test2 gtest pthread)
target_link_libraries(test3 gtest pthread)
target_link_libraries(test4 gtest pthread)

enable_testing()
add_test(NAME test1 COMMAND test1)
add_test(NAME test2 COMMAND test2)
add_test(NAME test3 COMMAND test3)
add_test(NAME test4 COMMAND test4)
set_tests_properties(test1 PROPERTIES LABELS alpha)
set_tests_properties(test2 PROPERTIES LABELS alpha)
set_tests_properties(test3 PROPERTIES LABELS beta)
set_tests_properties(test4 PROPERTIES LABELS beta)


