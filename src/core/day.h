#pragma once

#include <map>
#include <vector>
#include <string>
#include <QString>

/**
 * @brief This struct describes temperature information
 * 
 */
struct Temperature {
    float max;
    float average;
    float min;
};

/**
 * @brief This struct describes precipitation information
 * 
 */
struct Precipitation {
    float max;
    float average;
    float min;
    float sum;
};

/**
 * @brief This struct describes climate data
 * 
 */
struct ClimateData {
    Temperature max_temperature;
    Temperature avg_temperature;
    Temperature min_temperature;
    Precipitation precipitation;
    Precipitation snow_depth;
};

/**
 * @brief   This class describes the Day instance
 * 
 */
class Day
{
    public:
        Day(const std::string& filename);

        static QString monthFromInt(int month);
        static const std::vector<std::string> months;

        const std::vector<ClimateData>& getMonthData(const std::string& month) const; // Method to return info for Month
        const std::vector<ClimateData>& getMonthData(int month);

        void printMonthClimate(const std::string& month) const;  // Method to print the data for the given month
        void printClimateData() const;  // Method to print the data
        float getRandomTemperatureValue(const Temperature& temperature) const;
        float getRandomPrecipitationValue(const Precipitation& precipitation) const;

        int currentDay() const;
        int month() const;
        QString monthId() const;
        void nextDay();

    private:
        std::map<std::string, std::vector<ClimateData>> climateData;
        void loadClimateData(const std::string& filename);

        int day = 1;
};