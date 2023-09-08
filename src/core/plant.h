#pragma once

#include <QMap>
#include <QString>
#include <QList>
#include <QPair>

/**
* @brief    This struct contain the effect 
* 
*/
struct PlantEffect
{
    int healthBar;
    int thirstBar;
    int hungerBar;
    int moraleBar;
    int energyBar;
};

/**
 * @brief   This struct contain the info of Plant
 * 
 */
struct PlantInfo
{
    QString name;
    QString category;
    bool edible;
    PlantEffect effect;
};

/**
 * @brief   This class describe the plant instance
 * 
 */
class Plant {
public:
    // Constructor to initialize plants from JSON file
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