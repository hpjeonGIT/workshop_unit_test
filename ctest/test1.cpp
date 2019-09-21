#include "gtest/gtest.h"

class MyTest1 : public ::testing::Test {
public:
    float var1;
    double var2;
};

TEST_F(MyTest1, testExpectFloat) {
    var1=1.0f;
    EXPECT_FLOAT_EQ(var1, 1.0f);
    var1 -= 1.0f;
    var1 += 1.1f;
    EXPECT_FLOAT_EQ(var1, 1.0f);
}

TEST_F(MyTest1, testExpectDouble) {
    var2=1.0;
    EXPECT_DOUBLE_EQ(var2, 1.0);
    var2 -= 1.0;
    var2 += 1.0;
    EXPECT_DOUBLE_EQ(var2, 1.0);
}

int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
