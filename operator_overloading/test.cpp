#include <sstream>
#include <ostream>
#include <iostream>
#include <string>

inline std::stringstream& operator<<(std::stringstream& ss, bool const& tf) {
  std::cout << "BOOL 1\n";
  std::string yn = (tf) ? "TRUE" : "FALSE";
  ss << yn;
  return (ss);
}

inline std::stringstream& operator<<(std::stringstream& ss, bool & tf) {
  std::cout << "BOOL 2\n";
  std::string yn = (tf) ? "TRUE" : "FALSE";
  ss << yn;
  return (ss);
}

inline std::stringstream& operator<<(std::stringstream& ss, const char word[]) {
  std::cout << "BOOL 3\n";  
  ss << std::string(word);
  return (ss);
}

template <typename T>
inline std::stringstream& operator<<(std::stringstream& ss, T const& unknown) {
  std::cout << "unknown data type\n";
  return (ss);
}

int main(int argc, char** argv) {
  std::stringstream myoutput;
  bool mybool = true;
  myoutput << true << mybool << " SOME words here " << true;
  std::cout << myoutput.str() << std::endl;
  return 0;
}
/*
$ g++ -std=c++14 -g test.cpp 
$ ./a.out 
BOOL 1  <- this is from myoutput << true
BOOL 2  <- this is from true << mybool
BOOL 3  <- this is from mybool << " SOME 
BOOL 1  <- this is from here " << true
TRUETRUE SOME words here TRUE
*/
