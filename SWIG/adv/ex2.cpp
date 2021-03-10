#include <vector>

int my_vec_sum(std::vector<int> nv) {
   int nsum = 0;
   for (auto x : nv){
       nsum += x;
   }
   return nsum;
}

