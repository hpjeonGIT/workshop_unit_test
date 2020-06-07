#include "number.h"
#include <iostream>
#include <vector>

Number::Number(int start) { 
   data = start; 
   std::cout << "Number: " << data << std::endl;
}

Number::~Number(  ) { 
   std::cout << "~Number: " << data << std::endl; 
}

void Number::add_v(std::vector<int> nv) { 
   int nsum = 0;
   for (auto x: nv) { nsum += x;}
   data += nsum; 
   std::cout << "add " << nsum << std::endl; 
}

void Number::add(int value) { 
   data += value; 
   std::cout << "add " << value << std::endl; 
}

void Number::sub(int value) { 
   data -= value; 
   std::cout << "sub " << value << std::endl; 
}

void Number::display(  ) { 
   std::cout << "Number = " << data << std::endl; 
}
