#pragma once

#include <QMap>
#include <QString>
#include <QList>
#include <QPair>

/**
 * @brief This struct contains animal info
 * 
 */
struct AnimalInfo
{
    QString speciesID;
    QString category;
    QString name;
};

/**
 * @brief This class describes the animal instance
 * 
 */
class Animal {
public:
    Animal(const QString& filePath);
    void loadAnimalsFromJson(const QString& filePath);
    const AnimalInfo& getRandomAnimal() const;
    const AnimalInfo& getRandomAnimalInCategory(const QString& category) const;
    QString getRandomAnimalCategory() const;

private:
    // Animal elements
    QMap<QString, QList<AnimalInfo>> animals;
};





