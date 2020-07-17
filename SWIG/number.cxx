#include "number.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <memory>
#include <string>

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

void Number::timedata(std::time_t x) {
   std::cout << "time data = " << x << std::endl;
}

void Number::shtest(int value) {
    n1 = std::make_shared<int>(value);
    std::cout << n1.use_count() << " " << n1.get() <<std::endl;
}

void Parent::print_p() {
    std::cout << "id_p=" << id_p << std::endl;
}
void Child::print_c() {
    std::cout << "id_c=" << id_c << std::endl;
}

void mytest::print_mytest() {
    abc.get()->print_c();
}

void mytest::activate(std::string txt) {
    if (txt.compare("Parent") == 0) {
	p1 = std::make_shared<Parent>(10);
	std::cout << "p1 is activated\n";
    } else {
	c1 = std::make_shared<Child>(100);
	std::cout << "c1 is activatged\n";
    }
}
