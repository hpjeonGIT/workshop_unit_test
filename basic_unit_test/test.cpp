#include "gmock/gmock.h"
#include "../md_basic.h"
#include <iostream>
using namespace testing;

class MD_test: public Test{
public:
    Particle<double> q;
};

TEST_F(MD_test, basictest1) {
    ASSERT_THAT(q.xm,1.0);
}



TEST_F(MD_test, basictest2) {
    for(std::size_t i=0; i< 3; i++)
	std::cout << q.xx[i] << " jeonb " << std::endl;
    ASSERT_THAT(q.xx[0],1.0);
}

