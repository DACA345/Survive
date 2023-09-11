#include <gtest/gtest.h>
#include <core/day.h>

TEST(DayTest, GetRandomTemperatureValueTest)
{
    Day testDay("data/levels/mtaspiring/climate.json");

    // Print data for all months
    testDay.printClimateData();

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
        float randomMaxTemp = testDay.getRandomTemperatureValue(data.maxTemperature);
        EXPECT_GE(randomMaxTemp, data.maxTemperature.min); // Check if random max temp is >= min
        EXPECT_LE(randomMaxTemp, data.maxTemperature.max); // Check if random max temp is <= max

        float randomAvgTemp = testDay.getRandomTemperatureValue(data.avgTemperature);
        EXPECT_GE(randomAvgTemp, data.avgTemperature.min); // Check if random avg temp is >= min
        EXPECT_LE(randomAvgTemp, data.avgTemperature.max); // Check if random avg temp is <= max

        float randomMinTemp = testDay.getRandomTemperatureValue(data.minTemperature);
        EXPECT_GE(randomMinTemp, data.minTemperature.min); // Check if random min temp is >= min
        EXPECT_LE(randomMinTemp, data.minTemperature.max); // Check if random min temp is <= max
    }
}

TEST(DayTest, DayProgressionTests)
{
    Day testDay("data/levels/mtaspiring/climate.json");

    EXPECT_EQ(testDay.currentDay(), 1);

    testDay.nextDay();

    EXPECT_EQ(testDay.currentDay(), 2);

    EXPECT_EQ(testDay.month(), 1);
    EXPECT_EQ(testDay.monthId(), QString("JAN"));

    for (short i = 0; i < 30; i++)
    {
        testDay.nextDay();
    }

    EXPECT_EQ(testDay.currentDay(), 32);
    EXPECT_EQ(testDay.month(), 2);
    EXPECT_EQ(testDay.monthId(), QString("FEB"));
}