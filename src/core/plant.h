#pragma once

#include <QMap>
#include <QString>
#include <QList>
#include <QPair>

class Plant {
public:
    // Constructor to initialize animals from JSON file
    Plant(const QString& filePath);

    // Method to load plants from json
    void loadPlantsFromJson(const QString& filePath);
    
    // Method to return plant according to category and also it's status for edible or not
    QPair<QString, bool> getRandomPlant(const QString& category);

private:
    QMap<QString, QList<QPair<QString, bool>>> plants;
};