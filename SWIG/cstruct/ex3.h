#include <string>
struct segm {
    int _0;
    std::string _1;
	segm() {} // when no initialization list is given
	segm(int i, std::string s) // constructor
	{
		_0 = i;
		_1 = s;
	}
};
