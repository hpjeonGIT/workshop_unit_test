%module ex3
%include "std_string.i"
%{
  #include "ex3.h"
  extern void test01(segm x);
  extern void test01(int i, std::string s);
%}

%include "ex3.h"
extern void test01(segm x);
extern void test01(int i, std::string s);
