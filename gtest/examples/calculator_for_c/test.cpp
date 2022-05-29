/* main.cpp */
#include "gtest/gtest.h"

extern "C" {
#include "calculator.h"
}

TEST(tc_basic, plus_1)
{
    EXPECT_EQ(2, plus(1, 1));
    EXPECT_EQ(0, plus(1, -1));
}

TEST(tc_basic, minus_1)
{
    EXPECT_EQ(0, minus(1, 1));
    EXPECT_EQ(0, minus(-1, -1));
}

TEST(tc_basic, multiply_1)
{
    EXPECT_EQ(1, multiply(1, 1));
    EXPECT_EQ(-1, multiply(-1, 1));
}

TEST(tc_basic, divide_1)
{
    EXPECT_EQ(1, divide(1, 1));
    EXPECT_EQ(-1, divide(-1, 1));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}