#include<regex>
#include<iostream>
#include<fstream>
#include<string>
#include<set>

std::string Extract_arg(const std::string& line,
						const std::regex& re){
	std::smatch m;
	size_t s = line.find_first_not_of(' ');
	if (s == std::string::npos) return "";
	if (line[s] == '#') return ""; // comment found
	std::regex_search(line, m, re);
	if (m.size() <2) return "";
	auto args = m.str(2);
	std::regex_search(args, m, std::regex(".*\\,\\s*'(.+?)'\\s*",
					  std::regex_constants::icase));
	//for (auto x: m) std::cout << args <<  " arguments= " << x << std::endl;
	return m.str(1);
}

int main(int argc, char** argv) {
	std::ifstream inp("input.txt");
	std::regex const rule(".*(Win.create)\\s*\\((.+?)\\)", std::regex_constants::icase);
	std::set<std::string> alist;
	std::string line;
	while (std::getline(inp,line)) {
		auto m = Extract_arg(line, rule);

		if (!m.empty()) {
			//std::cout << "found match " << m << std::endl;
			alist.insert(m);
		}


	}
	for(auto x: alist) std::cout << " 2nd argument = " << x << std::endl;
}
