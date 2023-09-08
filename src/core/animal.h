#pragma once

#include <QMap>
#include <QString>
#include <QList>
#include <QPair>

/**
*  @brief This struct contains the effects
* 
*/
struct AnimalEffect
{
    int healthBar;
    int thirstBar;
    int hungerBar;
    int moraleBar;
    int energyBar;
};

/**
 * @brief Struct representation of the JSON animal info.
 * 
 */
struct AnimalInfo
{
    QString speciesID;
    QString category;
    QString name;
    bool edible;
    AnimalEffect effect;

};

/**
 * @brief This class contains the animals from a JSON.
 * 
 */
class Animal {
    public:
        /**
         * @brief      Constructs a new instance from a JSON of animals.
         * @see        loadAnimalsFromJson
         *
         * @param[in]  filePath  The file path
         */
        Animal(const QString& filePath);

        /**
         * @brief      Loads the animals from json.
         *
         * @param[in]  filePath  The file path
         */
        void loadAnimalsFromJson(const QString& filePath);

        /**
         * @brief      Gets a random animal.
         *
         * @return     The random animal.
         */
        const AnimalInfo& getRandomAnimal() const;

        /**
         * @brief      Gets a random animal in category.
         *
         * @param[in]  category  The category
         *
         * @return     The random animal in the category.
         */
        const AnimalInfo& getRandomAnimalInCategory(const QString& category) const;

        /**
         * @brief      Gets a random animal category.
         *
         * @return     The random animal category.
         */
        QString getRandomAnimalCategory() const;

    private:
        /**
         * Stores the animals based on category.
         */
        QMap<QString, QList<AnimalInfo>> animals;
};





