#include <gtest/gtest.h>
#include <Core/season.h>

TEST(SeasonTest, MethodConstructorTest)
{
    Season season("data/levels/mtaspiring/season.json");

    EXPECT_STREQ(season.getSeason("JAN").toStdString().c_str(), "summer");
    EXPECT_STREQ(season.getSeason("APR").toStdString().c_str(), "autumn");
    EXPECT_STREQ(season.getSeason("JUL").toStdString().c_str(), "winter");
    EXPECT_STREQ(season.getSeason("OCT").toStdString().c_str(), "spring");

    EXPECT_STREQ(season.getSeason("RAW").toStdString().c_str(), "No seasons found");
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


