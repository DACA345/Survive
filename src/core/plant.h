#pragma once

#include <QMap>
#include <QString>
#include <QList>
#include <QPair>

struct PlantInfo
{
    QString name;
    QString category;
    bool edible;
};

class Plant {
    public:
        // Constructor to initialize animals from JSON file
        Plant(const QString& filePath);

        // Method to load plants from json
        void loadPlantsFromJson(const QString& filePath);
    
        // Method to return plant according to category and also it's status for edible or not
        const PlantInfo& getRandomPlant() const;
        const PlantInfo& getRandomPlantInCategory(const QString& category) const;
        QString getRandomPlantCategory() const;

    private:
        QMap<QString, QList<PlantInfo>> plants;
};