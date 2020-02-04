1.
```
#include <iostream>
#include <vector>

template<typename T> class matrix {
public:
    matrix() : local_size(5.) {}
    matrix(int A) : local_size(A) {}
    ~matrix() = default;
    virtual void say_hello() {
	std::cout << "hello from matrix \n";
    }
protected:
    T local_size;
};

template<typename T> class derived: public matrix <T> {
public:
    derived() : any_size(3.0) {}
    ~derived() = default;
    void print_local_size() {
	std::cout << "local size = " << local_size << std::endl;
    }
private:
    T any_size;
};

int main(int argc, char** argv) {
    derived<double> drv;
    drv.print_local_size();
    return 0;
}
```
- The above code yields `error: ‘local_size’ was not declared in this scope` when compiled as g++ -std=c++14 template_class_test.cpp
- Why?
  - Due to template, local_size is NOT determined. Compiler will not able to find it
  - Ref: https://stackoverflow.com/questions/7076169/not-declared-in-this-scope-error-with-templates-and-inheritance
- How to fix?
  - Use this->local_size
```
#include <iostream>
#include <vector>

template<typename T> class matrix {
public:
    matrix() : local_size(5.) {}
    matrix(int A) : local_size(A) {}
    ~matrix() = default;
    virtual void say_hello() {
	std::cout << "hello from matrix \n";
    }
protected:
    T local_size;
};

template<typename T> class derived: public matrix <T> {
public:
    derived() : any_size(3.0) {}
    ~derived() = default;
    void print_local_size() {
	std::cout << "local size = " << this->local_size << std::endl;
    }
private:
    T any_size;
};


int main(int argc, char** argv) {
    derived<double> drv;
    drv.print_local_size();
    return 0;
}
```
