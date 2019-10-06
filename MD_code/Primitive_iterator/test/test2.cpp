#include "gtest/gtest.h"
#include "md.h"

class MyTest2 : public ::testing::Test {
public:
    float var1;
    double var2;
};

TEST_F(MyTest2, testMDclass) {
    std::size_t n1 = 1000;
    MD sim1(n1);
    uint n2 = 1000;
    MD sim2(n2);
    EXPECT_EQ(sim1.getSizeofq(), n1);
    EXPECT_EQ(sim2.getSizeofq(), n2);
    EXPECT_EQ(sim1.getSizeofq(), sim2.getSizeofq());
}

int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
