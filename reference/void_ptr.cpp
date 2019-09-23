#include <iostream>

int main(int argc, char** argv)
{
    int i;
    int *j;
    void *k;
    i=1;
    j=&i;
    k=&i;
    std::cout << i << std::endl;
    i++;
    std::cout << *j << std::endl;
    int *m = static_cast<int*> (k);
    std::cout << *m << std::endl;
    return 0;
}
// Lesson: avoid void pointer
// Ref: https://www.quora.com/Why-is-using-void*-considered-bad-design-practice-in-C++-code
