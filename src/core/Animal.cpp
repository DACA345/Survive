#include "Animal.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Animal::Animal(const QString& jsonFilePath) {
    // Load animals from the JSON file and store them in the data structure.
    QFile file(jsonFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Error statement
        return;
    }

    QJsonDocument jsonData = QJsonDocument::fromJson(file.readAll());
    file.close();

    // Process birds
    QJsonArray birdsArray = jsonData["birds"].toArray();
    for (const QJsonValue& birdValue : birdsArray) {
        QJsonObject bird = birdValue.toObject();
        QString speciesID = bird["species_id"].toString();
        QString name = bird["name"].toString();
        birds.append({ speciesID, name });
    }

    // Process mammals
    QJsonArray mammalsArray = jsonData["mammals"].toArray();
    for (const QJsonValue& mammalValue : mammalsArray) {
        QJsonObject mammal = mammalValue.toObject();
        QString speciesID = mammal["species_id"].toString();
        QString name = mammal["name"].toString();
        mammals.append({ speciesID, name });
    }

    // Process fish
    QJsonArray fishesArray = jsonData["fishes"].toArray();
    for (const QJsonValue& fishesValue : fishesArray) {
        QJsonObject fish = fishesValue.toObject();
        QString speciesID = fish["species_id"].toString();
        QString name = fish["name"].toString();
        fishes.append({ speciesID, name });
    }

    // Process reptiles
    QJsonArray reptilesArray = jsonData["reptiles"].toArray();
    for (const QJsonValue& reptilesValue : reptilesArray) {
        QJsonObject reptile = reptilesValue.toObject();
        QString speciesID = reptile["species_id"].toString();
        QString name = reptile["name"].toString();
        reptiles.append({ speciesID, name });
    }

    // Process amphibians
    QJsonArray amphibiansArray = jsonData["amphibians"].toArray();
    for (const QJsonValue& amphibiansValue : amphibiansArray) {
        QJsonObject amphibian = amphibiansValue.toObject();
        QString speciesID = amphibian["species_id"].toString();
        QString name = amphibian["name"].toString();
        amphibians.append({ speciesID, name });
    }
}