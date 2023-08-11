#include <gtest/gtest.h>
#include <Core/Day.h>

TEST(DayTests, MethodConstructorTest)
{
    Day testDay("data/levels/mtaspiring/climate.json");

    // Print climate data for each month
    std::cout << "Climate Data for JAN:\n";
    testDay.printMonthClimate("jan");

    std::cout << "\nClimate Data for FEB:\n";
    testDay.printMonthClimate("FEB");


    // Test for a month that exists in the data (e.g., JAN)
    // std::vector<ClimateData> janData = testDay.getMonthData("jan");
    // Check if the returned vector is not empty
    // ASSERT_FALSE(janData.empty());  

    // Test for a month that does not exist in the data (e.g., meo)
    // std::vector<ClimateData> meoData = testDay.getMonthData("meo");
    // ASSERT_TRUE(meoData.empty());   // Check if the returned vector is empty
}