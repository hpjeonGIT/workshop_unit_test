#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>

int main(int argc, char** argv) {
    std::ofstream fout;
    std::string fname;
    std::time_t atime = 1234567;
    std::tm *ltm = std::localtime(&atime);
    fname = "test_file.txt";
    fout.open(fname);
    int yr = 1900 + ltm->tm_year;
    int mn = 1 + ltm->tm_mon;
    int dy = ltm->tm_mday;
    fout << "DATE = " << yr << "-"
         << std::setfill('0') << std::setw(2) << mn << "-"
         << std::setfill('0') << std::setw(2) << dy << "\n";
//
    std::tm ntm;
    ntm.tm_year = yr-1900;
    ntm.tm_mon = mn - 1;
    ntm.tm_mday = dy;
    fout << std::mktime(&ntm);
    fout.close();
    return 0;
}
/*
$ g++ -std=c++17 date_to_sec.cpp
$ ./a.out
$ more test_file.txt
DATE = 1970-01-15
1227600

$ date -d @1227600
Thu Jan 15 00:00:00 EST 1970
$ date -d @1234567
Thu Jan 15 01:56:07 EST 1970
*/
