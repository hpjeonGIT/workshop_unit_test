#include "gmock/gmock.h"
#include "../md_vector.h"
#include <iostream>
using namespace testing;

class MD_test: public Test{
private:
public:
    Particle<double> q;
    std::vector<ptclass<double>> v;
    virtual void SetUp() {
	std::cout << "jeonb setup" << std::endl;
	q = Particle<double>(100);
	v.resize(100);
    }
    virtual void TearDown() {
	std::cout << "jeonb teardown" << std::endl;
	// delete [] q; not necessary. Already deallocated
    }
};

TEST_F(MD_test, basictest1) {
    EXPECT_THAT(q.xm,1.0);
    std::cout << q.xm << " jeonb " << std::endl;
    EXPECT_THAT(v[75].xm ,11.1);
}



TEST_F(MD_test, basictest2) {
    EXPECT_THAT(q.xx[99],1.0);
    EXPECT_THAT(q.xx[89],1.0);
   for(std::size_t i=0; i< 3; i++)
	std::cout << q.xx[i] << " jeonb " << std::endl;
}

