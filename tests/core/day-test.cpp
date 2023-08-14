#include <gtest/gtest.h>
#include <Core/Day.h>

TEST(DayTest, GetRandomTemperatureValueTest)
{
    Day testDay("data/levels/mtaspiring/climate.json");

    // Print climate data for each month
    std::cout << "Climate Data for JAN:\n";
    testDay.printMonthClimate("jan");

    std::cout << "\nClimate Data for FEB:\n";
    testDay.printMonthClimate("FEB");

    // Test for a month that exists in the data (e.g., JAN)
    std::vector<ClimateData> janData = testDay.getMonthData("jan");
    // Check if the returned vector is not empty
    ASSERT_FALSE(janData.empty());

    // Test for a month that does not exist in the data (e.g., meo)
    std::vector<ClimateData> meoData = testDay.getMonthData("meo");
    ASSERT_TRUE(meoData.empty());   // Check if the returned vector is empty

    // Test the getRandomTemperatureValue function
    // Test getting random temperature value for each ClimateData in JAN
    for (const ClimateData& data : janData) 
    {
        float randomMaxTemp = testDay.getRandomTemperatureValue(data.max_temperature);
        EXPECT_GE(randomMaxTemp, data.max_temperature.min); // Check if random max temp is >= min
        EXPECT_LE(randomMaxTemp, data.max_temperature.max); // Check if random max temp is <= max

        float randomAvgTemp = testDay.getRandomTemperatureValue(data.avg_temperature);
        EXPECT_GE(randomAvgTemp, data.avg_temperature.min); // Check if random avg temp is >= min
        EXPECT_LE(randomAvgTemp, data.avg_temperature.max); // Check if random avg temp is <= max

        float randomMinTemp = testDay.getRandomTemperatureValue(data.min_temperature);
        EXPECT_GE(randomMinTemp, data.min_temperature.min); // Check if random min temp is >= min
        EXPECT_LE(randomMinTemp, data.min_temperature.max); // Check if random min temp is <= max
    }
}
