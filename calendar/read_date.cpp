#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
// https://en.cppreference.com/w/cpp/io/manip/get_time
int main() {
    struct tm t1 = {};
    std::istringstream ss("Dec-01-1987 00:00:01"); //0:0:01 will not work
    ss >> std::get_time(&t1, "%b-%d-%Y %H:%M:%S"); // %b for Mar, %m for 03
    if (ss.fail()) {
        std::cout << "failed\n";
    } else {
        std::cout << "passed\n";
    }
    std::time_t mydate = std::mktime(&t1);
    std::cout <<mydate << std::endl;
    std::cout << t1.tm_mday << " " << t1.tm_mon << " " << t1.tm_year << std::endl;

    // find how to use parse from chrono
    // from C++20...
}
