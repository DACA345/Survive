#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QPair>
#include <QRandomGenerator>

#include "plant.h"

#define STORE_PLANT_DATA(categoryName) \
    PlantInfo plantData; \
    plantData.name = name; \
    plantData.category = categoryName; \
    plantData.edible = edible; \
    plantData.effect.healthBar = plantEffect["healthBar"].toInt(); \
    plantData.effect.thirstBar = plantEffect["thirstBar"].toInt(); \
    plantData.effect.hungerBar = plantEffect["hungerBar"].toInt(); \
    plantData.effect.moraleBar = plantEffect["moraleBar"].toInt(); \
    plantData.effect.energyBar = plantEffect["energyBar"].toInt(); \
    plants[categoryName].append(plantData);

// Constructor to initialize animals from JSON file
Plant::Plant(const QString& filePath)
{
    loadPlantsFromJson(filePath);
}

void Plant::loadPlantsFromJson(const QString& filePath) 
{
    QFile jsonFile(filePath);

    if (!jsonFile.open(QIODevice::ReadOnly)) 
    {
        qWarning("Could not open plants JSON file");
        return;
    }

    QByteArray jsonData = jsonFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (doc.isNull() || !doc.isObject()) 
    {
        qWarning("Invalid JSON data");
        return;
    }

    QJsonObject jsonObj = doc.object();

    // Process Fungi
    QJsonArray fungiArray = jsonObj["fungi"].toArray();
    for (const QJsonValue& fungiValue : fungiArray) {
        QJsonObject fungi = fungiValue.toObject();
        QString name = fungi["name"].toString();
        bool edible = fungi["edible"].toBool();
        QJsonObject plantEffect = fungi["effect"].toObject();

        STORE_PLANT_DATA("fungi");
    }


    // Process Plant
    QJsonArray plantArray = jsonObj["plant"].toArray();
    for (const QJsonValue& plantValue : plantArray) 
    {
        QJsonObject plant = plantValue.toObject();
        QString name = plant["name"].toString();
        bool edible = plant["edible"].toBool();
        QJsonObject plantEffect = plant["effect"].toObject(); 

        STORE_PLANT_DATA("plant");
    }
}

const PlantInfo& Plant::getRandomPlant() const
{
    return getRandomPlantInCategory(getRandomPlantCategory());
}

// Method to print our random plant according to category and also return edible status
const PlantInfo& Plant::getRandomPlantInCategory(const QString& category) const
{
    const QList<PlantInfo>& plantList = plants[category];
    if (plantList.isEmpty())
    {
        qFatal("No plants found");
    }

    return plantList[QRandomGenerator::global()->bounded(plantList.size())];
}

QString Plant::getRandomPlantCategory() const
{
    const QList<QString>& plantCategory = plants.keys();
    if (plantCategory.isEmpty())
    {
        qFatal("No plants found");
    }

    return plantCategory[QRandomGenerator::global()->bounded(plantCategory.size())];
}
