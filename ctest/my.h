# include <iostream>

class MyClass{
private:
    int myrank;
public:
    MyClass() {
	myrank = 1234;
    }
    void printrank();
    ~MyClass() {
    }
};
