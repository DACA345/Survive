#include "Animal.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QRandomGenerator>


// Constructor to initialize animals from JSON file
Animal::Animal(const QString& filePath) {
    loadAnimalsFromJson(filePath);
}

void Animal::loadAnimalsFromJson(const QString& filePath) {
    QFile jsonFile(filePath);

    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qWarning("Could not open animals JSON file");
        return;
    }

    QByteArray jsonData = jsonFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (doc.isNull() || !doc.isObject()) {
        qWarning("Invalid JSON data");
        return;
    }

    QJsonObject jsonObj = doc.object();

    // Process birds
    QJsonArray birdsArray = jsonObj["birds"].toArray();
    for (const QJsonValue& birdValue : birdsArray) {
        QJsonObject bird = birdValue.toObject();
        QString speciesID = bird["species_id"].toString();
        QString name = bird["name"].toString();
        animals["birds"].append(name);
    }

    // Process mammals
    QJsonArray mammalsArray = jsonObj["mammals"].toArray();
    for (const QJsonValue& mammalValue : mammalsArray) {
        QJsonObject mammal = mammalValue.toObject();
        QString speciesID = mammal["species_id"].toString();
        QString name = mammal["name"].toString();
        animals["mammals"].append(name);
    }

    // Process fish
    QJsonArray fishArray = jsonObj["fish"].toArray();
    for (const QJsonValue& fishValue : fishArray) {
        QJsonObject fish = fishValue.toObject();
        QString speciesID = fish["species_id"].toString();
        QString name = fish["name"].toString();
        animals["fish"].append(name);
    }

    // Process reptiles
    QJsonArray reptilesArray = jsonObj["reptiles"].toArray();
    for (const QJsonValue& reptileValue : reptilesArray) {
        QJsonObject reptile = reptileValue.toObject();
        QString speciesID = reptile["species_id"].toString();
        QString name = reptile["name"].toString();
        animals["reptiles"].append(name);
    }

    // Process amphibians
    QJsonArray amphibiansArray = jsonObj["amphibians"].toArray();
    for (const QJsonValue& amphibianValue : amphibiansArray) {
        QJsonObject amphibian = amphibianValue.toObject();
        QString speciesID = amphibian["species_id"].toString();
        QString name = amphibian["name"].toString();
        animals["amphibians"].append(name);
    }
}
// Get a random animal from each category
QString Animal::getRandomBird() const 
{
    QVector<QString> birds = animals["birds"];
    int index = QRandomGenerator::global()->bounded(birds.size());
    return birds[index];
}

QString Animal::getRandomMammal() const 
{
    QVector<QString> mammals = animals["mammals"];
    int index = QRandomGenerator::global()->bounded(mammals.size());
    return mammals[index];
}

QString Animal::getRandomFish() const 
{
    QVector<QString> fishes = animals["fishes"];
    int index = QRandomGenerator::global()->bounded(fishes.size());
    return fishes[index];
}

QString Animal::getRandomReptile() const 
{
    QVector<QString> reptiles = animals["reptiles"];
    int index = QRandomGenerator::global()->bounded(reptiles.size());
    return reptiles[index];
}

QString Animal::getRandomAmphibian() const 
{
    QVector<QString> amphibians = animals["amphibians"];
    int index = QRandomGenerator::global()->bounded(amphibians.size());
    return amphibians[index];
}