#include "gtest/gtest.h"
#include "md.h"

class MyTest3 : public ::testing::Test {
public:
    float var1;
    double var2;
};

TEST_F(MyTest3, testMDclass) {
    std::size_t n1 = 1000;
    MD sim3(n1);
    sim3.data_read();
    EXPECT_EQ(sim3.getSize_ngbr(), n1);
}

int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
