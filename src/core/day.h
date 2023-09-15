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
    double max;
    double average;
    double min;
};

/**
 * @brief This struct describes precipitation information
 * 
 */
struct Precipitation {
    double max;
    double average;
    double min;
    double sum;
};

/**
 * @brief This struct describes climate data
 * 
 */
struct ClimateData {
    Temperature maxTemperature;
    Temperature avgTemperature;
    Temperature minTemperature;
    Precipitation precipitation;
    Precipitation snowDepth;
};

/**
 * @brief   This class describes an in-game day with climate info.
 * 
 */
class Day
{
    public:
        /**
         * @brief      Makes a new day with climate data from a JSON file.
         * @see        loadClimateData
         *
         * @param[in]  filename  The filename
         */
        Day(const std::string& filename, const int& day = 1);

        /**
         * @brief      Convert an int value of a month to a string.
         *
         * @param[in]  month  The month
         *
         * @return     The month id.
         */
        static QString monthFromInt(int month);

        /**
         * List of month IDs
         */
        static const std::vector<std::string> months;

        /**
         * @brief      Gets the month data.
         *
         * @param[in]  month  The month
         *
         * @return     The month data.
         */
        const std::vector<ClimateData>& getMonthData(const std::string& month) const;

        /**
         * @brief      Gets the month data.
         *
         * @param[in]  month  The month
         *
         * @return     The month data.
         */
        const std::vector<ClimateData>& getMonthData(int month);

        /**
         * @brief      Gets a random temperature value.
         *
         * @param[in]  temperature  The temperature range
         *
         * @return     The random temperature value.
         */
        double getRandomTemperatureValue(const Temperature& temperature) const;

        /**
         * @brief      Gets a random precipitation value.
         *
         * @param[in]  precipitation  The precipitation range
         *
         * @return     The random precipitation value.
         */
        double getRandomPrecipitationValue(const Precipitation& precipitation) const;

        /**
         * @brief      Gets the current in-game day.
         *
         * @return     The day.
         */
        int currentDay() const;

        /**
         * @brief      Gets the current in-game month.
         *
         * @return     The month.
         */
        int month() const;

        /**
         * @brief      Gets the current in-game month id.
         *
         * @return     The month ID.
         */
        QString monthId() const;

        /**
         * @brief      Advances the day.
         */
        void nextDay();

    private:
        /**
         * Stores the climate data per month.
         */
        std::map<std::string, std::vector<ClimateData>> climateData;

        /**
         * @brief      Loads the climate data from a JSON.
         *
         * @param[in]  filename  The filename
         */
        void loadClimateData(const std::string& filename);

        /**
         * The current day.
         */
        int day = 1;
};