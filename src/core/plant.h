#pragma once

#include <QMap>
#include <QString>
#include <QList>
#include <QPair>

/**
 * @brief   This struct contain the info of Plant
 * 
 */
struct PlantInfo
{
    QString name;
    QString category;
    bool edible;
};

/**
 * @brief   This class describe the plant instance
 * 
 */
class Plant {
    public:
        /**
         * @brief      Constructs a new instance from a JSON of plants.
         * @see        loadPlantsFromJson
         * 
         * @param[in]  filePath  The file path
         */
        Plant(const QString& filePath);

        /**
         * @brief      Loads the plants from a JSON.
         *
         * @param[in]  filePath  The file path
         */
        void loadPlantsFromJson(const QString& filePath);
        
        /**
         * @brief      Gets a random plant.
         *
         * @return     The random plant.
         */
        const PlantInfo& getRandomPlant() const;

        /**
         * @brief      Gets a random plant in the category.
         *
         * @param[in]  category  The category
         *
         * @return     The random plant in the category.
         */
        const PlantInfo& getRandomPlantInCategory(const QString& category) const;

        /**
         * @brief      Gets a random plant category.
         *
         * @return     The random plant category.
         */
        QString getRandomPlantCategory() const;

    private:
        /**
         * Stores the plants per category.
         */
        QMap<QString, QList<PlantInfo>> plants;
};