// g++ -std=c++11 test_pointer.cpp
#include <iostream>
#include <vector>
#include <memory>

void foo(std::vector<int> &abc) {
  std::cout << abc.size() << std::endl;
  for(int i =0 ; i< abc.size(); i++) {
    std::cout << abc[i] << std::endl;;
  }
}

int main(int argc , char** argv) {
  std::shared_ptr<std::vector<int>> Ap_;
  std::shared_ptr<std::vector<int>> Ap_d_;   
  Ap_ = std::make_shared<std::vector<int>>(3,1);
  std::vector<int>* Ap_abc = dynamic_cast<std::vector<int>*>(Ap_.get());
  Ap_d_ = std::make_shared<std::vector<int>>(*Ap_abc);
 

  foo(*Ap_d_);
  return 0;
}
