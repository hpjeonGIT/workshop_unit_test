#include "gtest/gtest.h"
#include "md.h"

class MyTest1 : public ::testing::Test {
public:
    float  var1, ans1;
    double var2, ans2;
};

TEST_F(MyTest1, testingNearestIntegerFtn) {
    var1 = 1.1f;
    ans1 = dnint(var1);
    EXPECT_FLOAT_EQ(ans1, 1.0f);
    var2 = 2.55;
    ans2 = dnint(var2);
    EXPECT_DOUBLE_EQ(ans2, 3.);
    var1 = -1.7f;
    ans1 = dnint(var1);
    EXPECT_FLOAT_EQ(ans1, -2.0f);
    var2 = -3.1;
    ans2 = dnint(var2);
    EXPECT_DOUBLE_EQ(ans2, -3.0);
}

TEST_F(MyTest1, testingParticleClass) {
    std::size_t ntest = 1000;
    Particle q(ntest);
    EXPECT_EQ(q.xm.size(), ntest);
    EXPECT_EQ(q.xx.size(), ntest);
    EXPECT_EQ(q.vx.size(), ntest);
    EXPECT_EQ(q.fx.size(), ntest);
    EXPECT_EQ(q.fz.size(), ntest);
}

int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
