#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QRandomGenerator>

#include "animal.h"

#define STORE_ANIMAL_DATA(categoryName) \
    AnimalInfo animalData; \
    animalData.name = name; \
    animalData.category = categoryName; \
    animalData.edible = edible; \
    animalData.effect.healthBar = animalEffect["healthBar"].toInt(); \
    animalData.effect.thirstBar = animalEffect["thirstBar"].toInt(); \
    animalData.effect.hungerBar = animalEffect["hungerBar"].toInt(); \
    animalData.effect.moraleBar = animalEffect["moraleBar"].toInt(); \
    animalData.effect.energyBar = animalEffect["energyBar"].toInt(); \
    animals[categoryName].append(animalData);

// Constructor to initialize animals from JSON file
Animal::Animal(const QString& filePath) 
{
    loadAnimalsFromJson(filePath);
}

void Animal::loadAnimalsFromJson(const QString& filePath) 
{
    QFile jsonFile(filePath);

    if (!jsonFile.open(QIODevice::ReadOnly)) 
    {
        qWarning("Could not open animals JSON file");
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

    // Process birds
    QJsonArray birdsArray = jsonObj["birds"].toArray();
    for (const QJsonValue& birdValue : birdsArray) 
    {
        QJsonObject bird = birdValue.toObject();
        QString speciesID = bird["species_id"].toString();
        QString name = bird["name"].toString();        
        bool edible = bird["edible"].toBool();

        QJsonObject animalEffect = bird["effect"].toObject();

        STORE_ANIMAL_DATA("birds");
    }

    // Process mammals
    QJsonArray mammalsArray = jsonObj["mammals"].toArray();
    for (const QJsonValue& mammalValue : mammalsArray)
    {
        QJsonObject mammal = mammalValue.toObject();
        QString speciesID = mammal["species_id"].toString();
        QString name = mammal["name"].toString();
        bool edible = mammal["edible"].toBool();

        QJsonObject animalEffect = mammal["effect"].toObject();
        
        STORE_ANIMAL_DATA("mammals");
    }

    // Process fish
    QJsonArray fishArray = jsonObj["fish"].toArray();
    for (const QJsonValue& fishValue : fishArray)
    {
        QJsonObject fish = fishValue.toObject();
        QString speciesID = fish["species_id"].toString();
        QString name = fish["name"].toString();        
        bool edible = fish["edible"].toBool();

        QJsonObject animalEffect = fish["effect"].toObject();

        STORE_ANIMAL_DATA("fish");
    }

    // Process reptiles
    QJsonArray reptilesArray = jsonObj["reptiles"].toArray();
    for (const QJsonValue& reptileValue : reptilesArray)
    {
        QJsonObject reptile = reptileValue.toObject();
        QString speciesID = reptile["species_id"].toString();
        QString name = reptile["name"].toString();        
        bool edible = reptile["edible"].toBool();

        QJsonObject animalEffect = reptile["effect"].toObject();

        STORE_ANIMAL_DATA("reptiles");
    }

    // Process amphibians
    QJsonArray amphibiansArray = jsonObj["amphibians"].toArray();
    for (const QJsonValue& amphibianValue : amphibiansArray)
    {
        QJsonObject amphibian = amphibianValue.toObject();
        QString speciesID = amphibian["species_id"].toString();
        QString name = amphibian["name"].toString();        
        bool edible = amphibian["edible"].toBool();

        QJsonObject animalEffect = amphibian["effect"].toObject();

        STORE_ANIMAL_DATA("amphibians");
    }
}

const AnimalInfo& Animal::getRandomAnimal() const
{
    return getRandomAnimalInCategory(getRandomAnimalCategory());
}

// Method to print our random animal according to category 
const AnimalInfo& Animal::getRandomAnimalInCategory(const QString& category) const
{
    const QList<AnimalInfo>& animalList = animals[category];
    if (animalList.isEmpty())
    {
        qFatal("No animals found");
    }

    return animalList[QRandomGenerator::global()->bounded(animalList.size())];
}

QString Animal::getRandomAnimalCategory() const
{
    const QList<QString>& animalCategory = animals.keys();
    if (animalCategory.isEmpty())
    {
        qFatal("No animals found");
    }

    return animalCategory[QRandomGenerator::global()->bounded(animalCategory.size())];
}
