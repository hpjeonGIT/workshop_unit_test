%module number
%include "std_vector.i"

namespace std{
 %template(vectori) vector<int>;
 %template(vectord) vector<double>;
};

%{
#include "number.h"
%}

%include number.h
