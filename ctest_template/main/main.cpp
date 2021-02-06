#include <iostream>
#include <fstream>
#include <string>

using std::ifstream;
using std::ofstream;
using std::string;
using std::getline;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
  string inFile = "";
  string outFile = "";
  if (argc == 3) {
    inFile = argv[1];
    outFile = argv[2];
  } else {
    cout << " needs 2 arguments " << endl;
    return 1;
  }
  //

  string line;
  ifstream myreadin(inFile);
  ofstream mywriteout(outFile);
  if (myreadin.is_open() && mywriteout.is_open())  {
    while ( getline (myreadin,line) )
    {
      cout << line << endl;
      mywriteout << "adding a new line\n";
      mywriteout << line << endl;
    }
    myreadin.close();
    mywriteout.close();
  }
  else cout << "Unable to open file";
  return 0;
}
