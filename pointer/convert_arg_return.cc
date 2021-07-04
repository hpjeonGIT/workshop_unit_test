#include <iostream>
#include <vector>
#include <memory>

struct mystr {
  int i;
  float x;
};

const mystr& convert(const mystr& value) {
  mystr *rv = new mystr;
  rv->i = value.i*10;
  rv->x = value.x*10;
  return *rv;
  // how to delete rv? valgrind yields memory leak
}

const std::shared_ptr<mystr> shared_convert(const mystr& value) {
  std::shared_ptr<mystr> rv (new mystr);
  *rv = value;
  // do some conversion
  rv->i = value.i*10;
  rv->x = value.x*10;
  return rv;
  // valgrind yields no memory leak
}

int main(int argc, char** argv) {
  std::vector<mystr> myv;
  mystr *a0 = new mystr;
  a0->i = 123;
  a0->x = 3.14f;
  myv.push_back(*a0);
  auto p = shared_convert(*a0); // this is OK
  myv.push_back(*p);
  auto q = convert(*a0); //valgrind yields memory leak
  myv.push_back(q); 
  delete a0;
  for(auto& tmp: myv) std::cout << tmp.i << " " << tmp.x << std::endl;
  return 0;
}

/* command to run
g++ -g  -std=c++14 rv.cc
valgrind --leak-check=yes ./a.out 
*/
