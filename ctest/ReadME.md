# Steps to run
- mkdir build
- cd build
- cmake ..
- make

# Running individual gtest executable
- ./test1
```
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from MyTest1
[ RUN      ] MyTest1.testExpectFloat
/home/hpjeon/hw/TDD/ctest_ex/1/test1.cpp:14: Failure
Expected equality of these values:
  var1
    Which is: 1.1
  1.0f
    Which is: 1
[  FAILED  ] MyTest1.testExpectFloat (0 ms)
[ RUN      ] MyTest1.testExpectDouble
[       OK ] MyTest1.testExpectDouble (0 ms)
[----------] 2 tests from MyTest1 (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] MyTest1.testExpectFloat

 1 FAILED TEST
```
- ./test2
```
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from MyTest2
[ RUN      ] MyTest2.testAssertFloat
[       OK ] MyTest2.testAssertFloat (0 ms)
[ RUN      ] MyTest2.testAssertDouble
[       OK ] MyTest2.testAssertDouble (0 ms)
[----------] 2 tests from MyTest2 (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
```
# Running ctest
- ctest
```
Test project /home/hpjeon/hw/TDD/ctest_ex/1/build
    Start 1: test1
1/2 Test #1: test1 ............................***Failed    0.00 sec
    Start 2: test2
2/2 Test #2: test2 ............................   Passed    0.00 sec

50% tests passed, 1 tests failed out of 2

Total Test time (real) =   0.01 sec

The following tests FAILED:
	  1 - test1 (Failed)
Errors while running CTest
```
