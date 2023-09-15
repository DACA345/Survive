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
// TODO(Callum): Should be from a json in levels
struct LevelConfig
{
    // Action probabilities
    // Food
    double findFoodNothing = 0.2;
    double findFoodAnimal = 0.3;

    int findFoodEnergy = 20;
    int plantPoison = 30;

    // Water
    double findWaterNothing = 0.2;
    double findCleanWater = 0.3;
    
    int waterThirst = 20;
    int waterPoison = 10;

    int findWaterEnergy = 20;

    // Rest
    int restHungerHeal = 60;
    int restThirstHeal = 60;

    int restEnergy = 30;
    int restWellHeal = 30;

    int restHunger = 15;
    int restThirst = 5;

    // Explore
    double exploreNothing = 0.1;
    double exploreAnimal = 0.1;
    double explorePlant = 0.2;

    int exploreHunger = 10;
    int exploreThirst = 10;

    int exploreNothingEnergy = 10;
    int exploreEnergy = 20;

    // Events
    double seasonEvent = 0.5;
    double seasonEventTrigger = 0.4;
    double eventTrigger = 0.05;

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