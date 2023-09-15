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

const std::vector<std::string> Day::months = {
    "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL",
    "AUG", "SEP", "OCT", "NOV", "DEC"
};

Day::Day(const std::string& filename, const int& day)
{
    loadClimateData(filename);
    this->day = day;
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
            cd.maxTemperature.max = 0.0;
            cd.maxTemperature.average = 0.0;
            cd.maxTemperature.min = 0.0;

            cd.avgTemperature.max = 0.0;
            cd.avgTemperature.average = 0.0;
            cd.avgTemperature.min = 0.0;

            cd.minTemperature.max = 0.0;
            cd.minTemperature.average = 0.0;
            cd.minTemperature.min = 0.0;

            cd.precipitation.max = 0.0;
            cd.precipitation.average = 0.0;
            cd.precipitation.min = 0.0;
            cd.precipitation.sum = 0.0;

            cd.snowDepth.max = 0.0;
            cd.snowDepth.average = 0.0;
            cd.snowDepth.min = 0.0;
            cd.snowDepth.sum = 0.0;
            cd.snowDepth.sum = 0.0;

            // Afternoon temp
            QJsonValue maxTemperatureValue = monthElement.value("max_temperature");
            if (maxTemperatureValue.isObject()) 
            {
                QJsonObject maxTemperatureObject = maxTemperatureValue.toObject();
                cd.maxTemperature.max = maxTemperatureObject.value("max").toDouble();
                cd.maxTemperature.average = maxTemperatureObject.value("average").toDouble();
                cd.maxTemperature.min = maxTemperatureObject.value("min").toDouble();
            }

            // Morning/Evening temp
            QJsonValue avgTemperatureValue = monthElement.value("avg_temperature");
            if (avgTemperatureValue.isObject()) 
            {
                QJsonObject avgTemperatureObject = avgTemperatureValue.toObject();
                cd.avgTemperature.max = avgTemperatureObject.value("max").toDouble();
                cd.avgTemperature.average = avgTemperatureObject.value("average").toDouble();
                cd.avgTemperature.min = avgTemperatureObject.value("min").toDouble();
            }

            // Night temp
            QJsonValue minTemperatureValue = monthElement.value("min_temperature");
            if (minTemperatureValue.isObject()) 
            {
                QJsonObject minTemperatureObject = minTemperatureValue.toObject();
                cd.minTemperature.max = minTemperatureObject.value("max").toDouble();
                cd.minTemperature.average = minTemperatureObject.value("average").toDouble();
                cd.minTemperature.min = minTemperatureObject.value("min").toDouble();
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
                cd.snowDepth.max = snowdepthObject.value("max").toDouble();
                cd.snowDepth.average = snowdepthObject.value("average").toDouble();
                cd.snowDepth.min = snowdepthObject.value("min").toDouble();
                cd.snowDepth.sum = snowdepthObject.value("sum").toDouble();
            }

            monthData.push_back(cd);
            
        }
        climateData[it.key().toStdString()] = monthData;
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
double Day::getRandomTemperatureValue(const Temperature& temperature) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(temperature.min, temperature.max);
    return dist(gen);
}

// Method to get a random value between min and max precipitation values
double Day::getRandomPrecipitationValue(const Precipitation& precipitation) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(precipitation.min, precipitation.max);
    return dist(gen);
}

QString Day::monthFromInt(int month)
{
    return QString::fromStdString(months[month]);
}

int Day::currentDay() const
{
    return day;
}

int Day::month() const
{
    return (day / 30) + 1;
}

QString Day::monthId() const
{
    return monthFromInt(month() - 1);
}

void Day::nextDay()
{
    day++;
}