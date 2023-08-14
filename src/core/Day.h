#include <map>
#include <vector>
#include <string>

struct Temperature {
    float max;
    float average;
    float min;
};

struct Precipitation {
    float max;
    float average;
    float min;
    float sum;
};

struct ClimateData {
    Temperature max_temperature;
    Temperature avg_temperature;
    Temperature min_temperature;
    Precipitation precipitation;
    Precipitation snow_depth;
};

class Day {
    public:
        Day(const std::string& filename);
        const std::vector<ClimateData>& getMonthData(const std::string& month) const; // Method to return info for Month
        void printMonthClimate(const std::string& month) const;  // Method to print the data for the given month
        void printClimateData() const;  // Method to print the data
        float getRandomTemperatureValue(const Temperature& temperature) const;
        float getRandomPrecipitationValue(const Precipitation& precipitation) const;
    private:
        std::map<std::string, std::vector<ClimateData>> climateData;
        void loadClimateData(const std::string& filename);
};      