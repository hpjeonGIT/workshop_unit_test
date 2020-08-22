#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

std::stringstream get_all_text(std::string file_name)
{
    std::ifstream file(file_name);
    std::string str, token, new_file;
    std::stringstream allstr;
    bool found_include = false, skip = false, padding = true;
    //ref: https://stackoverflow.com/questions/275355/c-reading-file-tokens
    while(std::getline(file,str))
    {
	std::istringstream line(str);
	while(line >> token){
	    if (found_include) {
		std::cout << "include file ="<< token << std::endl;
		found_include = false;
		new_file = token;
		new_file.erase(std::remove(new_file.begin(), new_file.end(), '\'' ), new_file.end());
		str = get_all_text(new_file).str();
		skip = false;
		padding = false;
	    } 
	    if (token.compare("include") == 0) {
		std::cout << "include found \n";
		found_include = true;
		skip = true;
	    }
	}
	if (!skip && !str.empty()) {
	    allstr << str ;
	    if (padding) allstr << "\n";
	    padding = true;
	}
    }
    return allstr;
}


int main(int argc, char**argv)
{
    std::stringstream allstr;
    allstr = get_all_text("first.txt");
    std::cout <<allstr.str() <<std::endl;
    return 0;
}
