%module number
%include "std_vector.i"

namespace std{
 %template(vectori) vector<int>;
 %template(vectord) vector<double>;
};

%{
#include "number.h"
typedef long time_t;
%}

typedef long time_t;
%include number.h
// http://www.swig.org/Doc1.3/SWIG.html Chapter 5.3.5 Typedef
// typedef definitions appearing in a SWIG interface are not propagated to the generated wrapper code
