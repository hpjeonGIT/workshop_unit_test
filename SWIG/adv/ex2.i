%module ex2
%include "std_vector.i"

namespace std{
 %template(vectori) vector<int>;
 %template(vectord) vector<double>;
};

%{
#include <vector>
extern int my_vect_sum(std::vector<int> nv);
%}

extern int my_vect_sum(std::vector<int> nv);
