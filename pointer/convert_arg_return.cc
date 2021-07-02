#include <iostream>
#include <vector>
#include <memory>

struct mystr {
  int i;
  float x;
};

const mystr& convert(const mystr& value) {
  mystr *rv = new mystr;
  rv->i = value.i;
  rv->x = value.x;
  return *rv;
  // how to delete rv? valgrind yields memory leak
}

const std::shared_ptr<mystr> shared_convert(const mystr& value) {
  std::shared_ptr<mystr> rv (new mystr);
  *rv = value;
  // do some conversion
  return rv;
  // valgrind yields no memory leak
}

int main(int argc, char** argv) {
  std::vector<mystr> myv;
  mystr *a0 = new mystr;
  a0->i = 123;
  a0->x = 3.14f;
  myv.push_back(*a0);
  auto p = shared_convert(*a0);
  myv.push_back(*p);
  delete a0;
  for(auto& tmp: myv) std::cout << tmp.i << " " << tmp.x << std::endl;
  return 0;
}
