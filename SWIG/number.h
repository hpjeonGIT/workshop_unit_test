//ref http://books.gigatux.nl/mirror/pythonprogramming/0596000855_python2-CHP-19-SECT-8.html
#include <vector>
#include <ctime>
#include <memory>
#include <string>
class Number
{
public:
    Number(int start);
    ~Number(  );
    void add_v(std::vector<int> nv);
    void add(int value);
    void sub(int value);
    void display(  );
    void timedata(std::time_t x);
    int data;
    std::vector<int> xyz;
    void shtest(int value);
    std::shared_ptr <int> n1;
};

class Parent
{
public:
    int id_p;

    Parent(int start) : id_p(start) {}
    ~Parent()=default;

    void print_p();
};

class Child : public Parent
{
public:
    int id_c;
    Child(int start) : id_c (start+10), Parent(start) {}
    ~Child()=default;
    void print_c();
};

class mytest
{
public:
    int id_test;
    std::shared_ptr<Child> abc;
    std::shared_ptr<Parent> p1;
    std::shared_ptr<Child> c1;
    mytest(int start) {
	id_test = start;
	abc = std::make_shared<Child>(id_test);
    }
    ~mytest() = default;
    void print_mytest();
    void activate(std::string txt);
};
