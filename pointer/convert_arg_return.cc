#include <iostream>
#include <vector>
#include <memory>

struct mystr {
  int i;
  float x;
};

mystr& convert(const mystr& value) {
  mystr *rv = new mystr;
  rv->i = value.i*10;
  rv->x = value.x*10;
  return *rv;
  // how to delete rv? valgrind yields memory leak
}

mystr& convert2(const mystr& value) {
  mystr rv(value);
  rv.i *= 2;
  rv.x *= 1.1;
  return rv;
  // no memory leak
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

const std::shared_ptr<mystr> shared_convert2(const mystr& value) {
  std::shared_ptr<mystr> rv = std::make_shared<mystr> (value);
  rv->i *= 2;
  rv->x *= 1.1;
  return rv;
  // valgrind yields no memory leak. No use of new
}

int main(int argc, char** argv) {
  std::vector<mystr> myv;
  mystr *a0 = new mystr;
  a0->i = 123;
  a0->x = 3.14f;
  myv.push_back(*a0);
  auto p = shared_convert2(*a0); 
  myv.push_back(*p);
  auto q = convert2(*a0); 
  myv.push_back(q); 
  delete a0;
  for(auto& tmp: myv) std::cout << tmp.i << " " << tmp.x << std::endl;
  return 0;
}

/* command to run
g++ -g  -std=c++14 rv.cc
valgrind --leak-check=yes ./a.out 
*/
