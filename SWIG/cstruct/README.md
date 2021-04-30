# Test of C-struct with Python in SWIG
## Steps to build
- swig -c++ -python ex3.i
- g++ -g -std=c++14 -fPIC -c ex3.cpp ex3_wrap.cxx -I/usr/include/python3.6
- g++ -shared ex3.o ex3_wrap.o -o _ex3.so
- constructor is necessary to initialize as x = segm(123,"hello")
- %include "std_string.i" in ex3.i to use std::string in ex3.h
```
>>> from ex3 import *
>>> test01(segm(123,'morning'))
integer = 123
string  = morning
```
- test01([123,'morning']) does not work
- In order to use test01(123,'morning'), needs to supply an overloaded function
