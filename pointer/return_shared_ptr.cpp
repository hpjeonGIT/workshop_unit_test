#include <iostream>
#include <memory>
using std::cout;

class perf {
public:
	perf() = default;
	~perf() = default;
	perf(int _i, int _j)
	: i(_i),
	j(_j) {}
	void print_ij() {
		cout << i <<" " <<  j << std::endl;
	}
private:
	int i, j;
};

std::shared_ptr<perf> get_shared0(){
	return std::make_shared<perf> (2,3);
}

std::shared_ptr<perf> get_shared1(){
	std::shared_ptr<perf> tmp(new perf(4,5));
	return tmp;
}
int main(int argc, char** arg) {
	perf abc;
	perf cde(1,2);
	abc.print_ij();
	cde.print_ij();
	auto x = get_shared0();
	x->print_ij();
	auto y = get_shared1();
	y->print_ij();
	return 0;
}
