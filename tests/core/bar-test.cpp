#include <gtest/gtest.h>
#include <core/bar.h>

TEST(BarTest, ValueConstructorTest)
{
    Bar bar(10);
    EXPECT_EQ(bar.getValue(), 10);

    bar.minus(1);
    EXPECT_EQ(bar.getValue(), 9);
}

TEST(BarTest, DefaultConstructorTest)
{
    Bar bar;
    EXPECT_EQ(bar.getValue(), BAR_MAX);
}

TEST(BarTest, AdditionTest)
{
    Bar bar(10);
    bar.plus(1);
    EXPECT_EQ(bar.getValue(), 11);

    bar.plus(100);
    EXPECT_EQ(bar.getValue(), BAR_MAX);

    bar.plus(0);
    EXPECT_EQ(bar.getValue(), BAR_MAX);

    EXPECT_FALSE(bar.isEmpty());

    bar.plus(-1);
    EXPECT_EQ(bar.getValue(), BAR_MAX - 1);
}

TEST(BarTest, ReductionTest)
{
    Bar bar(10);
    bar.minus(1);
    EXPECT_EQ(bar.getValue(), 9);

    bar.minus(100);
    EXPECT_EQ(bar.getValue(), BAR_MIN);

    bar.minus(0);
    EXPECT_EQ(bar.getValue(), BAR_MIN);

    EXPECT_TRUE(bar.isEmpty());

    bar.minus(-1);
    EXPECT_EQ(bar.getValue(), BAR_MIN + 1);
}