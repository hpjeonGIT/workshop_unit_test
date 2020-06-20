//ref http://books.gigatux.nl/mirror/pythonprogramming/0596000855_python2-CHP-19-SECT-8.html
#include <vector>
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
};
