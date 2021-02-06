# Code Project
- A template for ctest using cmake
- bash script for running multiple commands in a single add_test()

## Objectives
- Regression test, not unit-test

## Steps to use
- `cd ctest`
- `mkdir build; cd build`
- `cmake ..`
- `make -j 3`
- `make install`
- `ctest` # For unit-test
```
Test project /home/hpjeon/hw/ctest/build
    Start 1: test01
1/3 Test #1: test01 ...........................   Passed    0.00 sec
    Start 2: test02
2/3 Test #2: test02 ...........................   Passed    0.00 sec
    Start 3: test03
3/3 Test #3: test03 ...........................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =   0.02 sec
```
