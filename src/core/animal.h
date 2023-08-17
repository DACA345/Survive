#pragma once

#include <QMap>
#include <QString>
#include <QList>
#include <QPair>

struct AnimalInfo
{
    QString speciesID;
    QString category;
    QString name;
};

class Animal {
public:
    // Constructor to initialize animals from JSON file
    Animal(const QString& filePath);

    // Method to load plants from json
    void loadAnimalsFromJson(const QString& filePath);

    // Method to return plant according to category and also it's status for edible or not
    const AnimalInfo& getRandomAnimal() const;
    const AnimalInfo& getRandomAnimalInCategory(const QString& category) const;
    QString getRandomAnimalCategory() const;

private:
    QMap<QString, QList<AnimalInfo>> animals;
};





