#pragma once

#include <QString>

#include "animal.h"
#include "event.h"
#include "explore.h"
#include "plant.h"
#include "season.h"

/**
 * @brief   This struct contain the id and name of a Level
 * 
 */
struct LevelInfo
{
    QString id;
    QString name;
};

/**
 * @brief   This struct contains all probabilty of everything in level
 * 
 */
struct LevelConfig
{
    // Action probabilities
    // Food
    double findFoodNothing;
    double findFoodAnimal;

    int findFoodEnergy;
    int plantPoison;

    // Water
    double findWaterNothing;
    double findCleanWater;

    int waterThirst;
    int waterPoison;

    int findWaterEnergy;

    // Rest
    int restHungerHeal;
    int restThirstHeal;

    int restEnergy;
    int restWellHeal;

    int restHunger;
    int restThirst;

    // Explore
    double exploreNothing;
    double exploreAnimal;
    double explorePlant;

    int exploreHunger;
    int exploreThirst;

    int exploreNothingEnergy;
    int exploreEnergy;

    // Events
    double seasonEvent;
    double seasonEventTrigger;
    double eventTrigger;

    // Climate
    double climateMulti;
    double optimumMinTemp;
    double optimumMaxTemp;

    // Morale
    double moraleMulti;
    double optimumMorale;

};

/**
 * @brief   This class describes the level instance
 * 
 */
class Level
{
    public:
        /**
         * @brief      Constructs a new level instance.
         *
         * @param[in]  id    The level identifier
         */
        Level(const QString& id);

        /**
        * @brief      Copy constructor to copy a level.
        * 
        * @param[in]  level  The level
        */
        Level(const Level& level);

        /**
         * @brief      Destroys the object.
         */
        ~Level();

        /**
         * @brief      Gets a file path from inside the level folder.
         *
         * @param[in]  name  The name of the file
         *
         * @return     The file path.
         */
        QString file(const QString& name) const;
        
        /**
         * @brief      Gets the level info.
         *
         * @return     The level info.
         */
        const LevelInfo& getInfo() const;

        /**
         * @brief      Gets the level configuration.
         *
         * @return     The level configuration.
         */
        const LevelConfig& getConfig() const;

        /**
         * @brief      Gets the animal data.
         *
         * @return     The animals.
         */
        const Animal& getAnimals() const;

        /**
         * @brief      Gets the events data.
         *
         * @return     The events.
         */
        const Event& getEvents() const;

        /**
         * @brief      Gets the explore events data.
         *
         * @return     The explore events.
         */
        const Explore& getExplorer() const;

        /**
         * @brief      Gets the plants data.
         *
         * @return     The plants.
         */
        const Plant& getPlants() const;

        /**
         * @brief      Gets the seasons data.
         *
         * @return     The seasons.
         */
        const Season& getSeasons() const;

    private:
        /**
         * @brief      Loads a level.
         */
        void loadLevel();

        /**
         * The level information.
         */
        LevelInfo info;

        /**
         * Gets the level config.
         */
        LevelConfig config;
        
        /**
         * The animals.
         */
        Animal animals;

        /**
         * The events.
         */
        Event events;

        /**
         * The explore events.
         */
        Explore explorer;

        /**
         * The plants.
         */
        Plant plants;

        /**
         * The seasons.
         */
        Season seasons;
};