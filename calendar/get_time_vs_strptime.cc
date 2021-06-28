#include <ctime>
#include <iostream>
#include <iostream>

int main(int argc, char** argv) {
  std::istringstream ss("2011,01,04");
  std::tm tm = {};
  std::string s2 = "2011-01-04";
  strptime(s2.c_str(), "%Y-%m-%d", &tm);
  std::cout << std::mktime(&tm) << " " << 1900+tm.tm_year << " " << 1+tm.tm_mon << " " << tm.tm_mday << std::endl;
  s2 = "2011-1-4";
  strptime(s2.c_str(), "%Y-%m-%d", &tm);
  std::cout << std::mktime(&tm) << " " << 1900+tm.tm_year << " " << 1+tm.tm_mon << " " << tm.tm_mday << std::endl;
  ss >> std::get_time(&tm, "%Y,%b,%d"); // in gcc, get_time() cannot read 2011,1,4 - clang may be able to read though.
  std::cout << std::mktime(&tm) << " " << 1900+tm.tm_year << " " << 1+tm.tm_mon << " " << tm.tm_mday << std::endl;
  return 0; 
}
