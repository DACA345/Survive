#include <gtest/gtest.h>
#include <core/explore.h>

TEST(ExploreTest, MethodConstructorTest)
{
    Explore testExplore("data/levels/mtaspiring/explore.json");

    // Test for the "encounter" category
    EXPECT_NO_THROW(testExplore.getRandomExploreCategory());
    EXPECT_NO_THROW(testExplore.getRandomExplore());
    EXPECT_NO_THROW(testExplore.getRandomExploreInCategory("encounter"));

    ASSERT_FALSE(testExplore.getRandomExplore().exploreID == "");
    ASSERT_FALSE(testExplore.getRandomExplore().category == "");
}