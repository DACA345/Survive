#include <gtest/gtest.h>

#include <Core/Day.h>

TEST(DayTests, ConstructorJSONTest)
{
    Day testDay("data/levels/mtaspiring/climate.json");
    // testDay.printClimateData();

    // Print climate data for each month
    std::cout << "Climate Data for JAN:\n";
    testDay.printMonthClimate("jan");

    std::cout << "\nClimate Data for FEB:\n";
    testDay.printMonthClimate("FEB");


    // Test for a month that exists in the data (e.g., JAN)
    std::vector<ClimateData> janData = testDay.getMonthData("jan");
    std::vector<ClimateData> febData = testDay.getMonthData("feb");
    std::vector<ClimateData> marData = testDay.getMonthData("mar");
    std::vector<ClimateData> aprData = testDay.getMonthData("apr");
    std::vector<ClimateData> mayData = testDay.getMonthData("may");
    std::vector<ClimateData> junData = testDay.getMonthData("jun");
    std::vector<ClimateData> julData = testDay.getMonthData("jul");
    std::vector<ClimateData> augData = testDay.getMonthData("aug");
    std::vector<ClimateData> sepData = testDay.getMonthData("sep");
    std::vector<ClimateData> octData = testDay.getMonthData("oct");
    std::vector<ClimateData> novData = testDay.getMonthData("nov");
    std::vector<ClimateData> decData = testDay.getMonthData("dec"); 
    // Check if the returned vector is not empty
    ASSERT_FALSE(janData.empty());  
    ASSERT_FALSE(febData.empty());
    ASSERT_FALSE(marData.empty());
    ASSERT_FALSE(aprData.empty());
    ASSERT_FALSE(mayData.empty());
    ASSERT_FALSE(junData.empty());
    ASSERT_FALSE(julData.empty());
    ASSERT_FALSE(augData.empty());
    ASSERT_FALSE(sepData.empty());
    ASSERT_FALSE(octData.empty());
    ASSERT_FALSE(novData.empty());
    ASSERT_FALSE(decData.empty());

    // Test for a month that does not exist in the data (e.g., meo)
    std::vector<ClimateData> meoData = testDay.getMonthData("meo");
    ASSERT_TRUE(meoData.empty());   // Check if the returned vector is empty
}