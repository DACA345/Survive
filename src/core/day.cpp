#include <iostream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <sstream>

#include "day.h"

Day::Day(const std::string& filename)
{
    loadClimateData(filename);
}

void Day::loadClimateData(const std::string& filename) 
{
    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::ReadOnly)) 
    {
        qWarning("Couldn't open file.");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject j = doc.object();


    for (auto it = j.begin(); it != j.end(); ++it) 
    {
        std::vector<ClimateData> monthData;
        QJsonArray monthArray = it.value().toArray();
        for (auto val : monthArray) {
            QJsonObject monthElement = val.toObject();
            ClimateData cd;

            // Initialize each field to default values
            cd.max_temperature.max = 0.0;
            cd.max_temperature.average = 0.0;
            cd.max_temperature.min = 0.0;

            cd.avg_temperature.max = 0.0;
            cd.avg_temperature.average = 0.0;
            cd.avg_temperature.min = 0.0;

            cd.min_temperature.max = 0.0;
            cd.min_temperature.average = 0.0;
            cd.min_temperature.min = 0.0;

            cd.precipitation.max = 0.0;
            cd.precipitation.average = 0.0;
            cd.precipitation.min = 0.0;
            cd.precipitation.sum = 0.0;

            cd.snow_depth.max = 0.0;
            cd.snow_depth.average = 0.0;
            cd.snow_depth.min = 0.0;
            cd.snow_depth.sum = 0.0;
            cd.snow_depth.sum = 0.0;

            // Afternoon temp
            QJsonValue maxTemperatureValue = monthElement.value("max_temperature");
            if (maxTemperatureValue.isObject()) 
            {
                QJsonObject maxTemperatureObject = maxTemperatureValue.toObject();
                cd.max_temperature.max = maxTemperatureObject.value("max").toDouble();
                cd.max_temperature.average = maxTemperatureObject.value("average").toDouble();
                cd.max_temperature.min = maxTemperatureObject.value("min").toDouble();
            }

            // Morning/Evening temp
            QJsonValue avgTemperatureValue = monthElement.value("avg_temperature");
            if (avgTemperatureValue.isObject()) 
            {
                QJsonObject avgTemperatureObject = avgTemperatureValue.toObject();
                cd.avg_temperature.max = avgTemperatureObject.value("max").toDouble();
                cd.avg_temperature.average = avgTemperatureObject.value("average").toDouble();
                cd.avg_temperature.min = avgTemperatureObject.value("min").toDouble();
            }

            // Night temp
            QJsonValue minTemperatureValue = monthElement.value("min_temperature");
            if (minTemperatureValue.isObject()) 
            {
                QJsonObject minTemperatureObject = minTemperatureValue.toObject();
                cd.min_temperature.max = minTemperatureObject.value("max").toDouble();
                cd.min_temperature.average = minTemperatureObject.value("average").toDouble();
                cd.min_temperature.min = minTemperatureObject.value("min").toDouble();
            }

            // Rain
            QJsonValue precipitationValue = monthElement.value("precipitation");
            if (precipitationValue.isObject())
            {
                QJsonObject precipitationObject = precipitationValue.toObject();
                cd.precipitation.max = precipitationObject.value("max").toDouble();
                cd.precipitation.average = precipitationObject.value("average").toDouble();
                cd.precipitation.min = precipitationObject.value("min").toDouble();
                cd.precipitation.sum = precipitationObject.value("sum").toDouble();
            }

            // Snow
            QJsonValue snowdepthValue = monthElement.value("snowdepth");
            if (snowdepthValue.isObject())
            {
                QJsonObject snowdepthObject = snowdepthValue.toObject();
                cd.snow_depth.max = snowdepthObject.value("max").toDouble();
                cd.snow_depth.average = snowdepthObject.value("average").toDouble();
                cd.snow_depth.min = snowdepthObject.value("min").toDouble();
                cd.snow_depth.sum = snowdepthObject.value("sum").toDouble();
            }

            monthData.push_back(cd);
            
        }
        climateData[it.key().toStdString()] = monthData;
    }
}

void Day::printClimateData() const 
{
    for (const auto& pair : climateData) 
    {
        std::cout << "Month: " << pair.first << std::endl;
        for (const auto& cd : pair.second) 
        {
            std::cout << "Max Temperature Max: " << cd.max_temperature.max << std::endl;
            std::cout << "Max Temperature Average: " << cd.max_temperature.average << std::endl;
            std::cout << "Max Temperature Min: " << cd.max_temperature.min << std::endl;
            
            std::cout << "Average Temperature Max: " << cd.avg_temperature.max << std::endl;
            std::cout << "Average Temperature Average: " << cd.avg_temperature.average << std::endl;
            std::cout << "Average Temperature Min: " << cd.avg_temperature.min << std::endl;

            std::cout << "Min Temperature Max: " << cd.min_temperature.max << std::endl;
            std::cout << "Min Temperature Average: " << cd.min_temperature.average << std::endl;
            std::cout << "Min Temperature Min: " << cd.min_temperature.min << std::endl;

            std::cout << "Precipitation Max: " << cd.precipitation.max << std::endl;
            std::cout << "Precipitation Average: " << cd.precipitation.average << std::endl;
            std::cout << "Precipitation Min: " << cd.precipitation.min << std::endl;
            std::cout << "Precipitation Sum: " << cd.precipitation.sum << std::endl;

            std::cout << "Snowdepth Max: " << cd.snow_depth.max << std::endl;
            std::cout << "Snowdepth Average: " << cd.snow_depth.average << std::endl;
            std::cout << "Snowdepth Min: " << cd.snow_depth.min << std::endl;
            std::cout << "Snowdepth Sum: " << cd.snow_depth.sum << std::endl;
        }
    }
}

const std::vector<ClimateData>& Day::getMonthData(const std::string& month) const {
    // Convert the month name to uppercase (e.g., jan -> JAN)
    std::string uppercaseMonth = month;
    std::transform(uppercaseMonth.begin(), uppercaseMonth.end(), uppercaseMonth.begin(), ::toupper);

    // Search for the month in the climateData map
    auto it = climateData.find(uppercaseMonth);
    if (it != climateData.end()) {
        // Return the vector of ClimateData for the given month
        return it->second;
    }
    else {
        // If the month is not found, return an empty vector
        static std::vector<ClimateData> emptyVector; // Static variable to avoid returning a local variable
        return emptyVector;
    }
}

const std::vector<ClimateData>& Day::getMonthData(int month)
{
    return getMonthData(Day::months[month - 1]);
}

// Method to get a random value between min and max temperature values
float Day::getRandomTemperatureValue(const Temperature& temperature) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(temperature.min, temperature.max);
    return dist(gen);
}

// Method to get a random value between min and max precipitation values
float Day::getRandomPrecipitationValue(const Precipitation& precipitation) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(precipitation.min, precipitation.max);
    return dist(gen);
}

int Day::month() const
{
    return (day / 30) + 1;
}

void Day::nextDay()
{
    day++;
}

void Day::printMonthClimate(const std::string& month) const
{
    // Convert the month name to uppercase (e.g., jan -> JAN)
    std::string uppercaseMonth = month;
    std::transform(uppercaseMonth.begin(), uppercaseMonth.end(), uppercaseMonth.begin(), ::toupper);

    // Search for the month in the climateData map
    auto it = climateData.find(uppercaseMonth);
    if (it != climateData.end()) {
        // Get the vector of ClimateData for the given month
        const std::vector<ClimateData>& monthData = it->second;

        // Print the climate data for the month
        for (const ClimateData& data : monthData) {
            // Get random values for temperature fields
            float maxTemp = getRandomTemperatureValue(data.max_temperature);
            float avgTemp = getRandomTemperatureValue(data.avg_temperature);
            float minTemp = getRandomTemperatureValue(data.min_temperature);

            // Get random values for precipitation fields
            float maxPrecipitation = getRandomPrecipitationValue(data.precipitation);
            float avgPrecipitation = getRandomPrecipitationValue(data.precipitation);
            float minPrecipitation = getRandomPrecipitationValue(data.precipitation);
            
            std::cout << "Afternoon = " << maxTemp << std::endl;
            std::cout << "Day/Evening = " << avgTemp << std::endl;
            std::cout << "Night = " << minTemp << std::endl;
            std::cout << "precipitation (max) = " << maxPrecipitation << std::endl;
            std::cout << "precipitation (average) = " << avgPrecipitation << std::endl;
            std::cout << "precipitation (min) = " << minPrecipitation << std::endl;
            
        }
    }
    else {
        std::cout << "Climate data for month " << month << " not found." << std::endl;
    }
}
