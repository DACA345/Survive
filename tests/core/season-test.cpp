#include <gtest/gtest.h>
#include <core/season.h>

TEST(SeasonTest, MethodConstructorTest)
{
    Season season("data/levels/mtaspiring/season.json");

    EXPECT_EQ(season.getSeason("JAN"), "summer");
    EXPECT_EQ(season.getSeason("APR"), "autumn");
    EXPECT_EQ(season.getSeason("JUL"), "winter");
    EXPECT_EQ(season.getSeason("OCT"), "spring");
              
    EXPECT_EQ(season.getSeason("RAW"), "No seasons found");
}

TEST(SeasonTest, MethodGetMonthTest)
{
    Season season("data/levels/mtaspiring/season.json");

    EXPECT_TRUE(season.getMonth("summer").contains("JAN"));
    EXPECT_TRUE(season.getMonth("autumn").contains("MAR"));
    EXPECT_TRUE(season.getMonth("winter").contains("JUN"));
    EXPECT_TRUE(season.getMonth("spring").contains("SEP"));

    EXPECT_FALSE(season.getMonth("rawing").contains("null"));
    
}


