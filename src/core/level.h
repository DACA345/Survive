#pragma once

#include <QString>

#include "animal.h"
#include "event.h"
#include "plant.h"
#include "season.h"

struct LevelInfo
{
    QString id;
    QString name;
};

// NOTE(Callum): Should maybe be level dependent in level.json
struct LevelConfig
{
    // Action probabilities
    // Food
    double findFoodNothing = 0.2;
    double findFoodAnimal = 0.2;

    int animalHunger = 30;
    int plantHunger = 10;
    int plantPoison = 30;

    // Water
    double findWaterNothing = 0.2;
    double findCleanWater = 0.2;
    
    int waterThirst = 20;
    int waterPoison = 20;

    // Rest
    int restHungerHeal = 60;
    int restThirstHeal = 60;

    int restEnergy = 20;
    int restHealth = 30;

    // Events
    double seasonEvent = 0.5;
    double seasonEventTrigger = 0.4;
    double eventTrigger = 0.05;

    int eventNegativeHealth = 40;
    int eventPositiveHealth = 40;
};

class Level
{
    public:
        Level(const QString& id);
        ~Level();

        QString file(const QString& name) const;
        
        const LevelInfo& getInfo() const;
        const LevelConfig& getConfig() const;

        const Animal& getAnimals() const;
        const Event& getEvents() const;
        const Plant& getPlants() const;
        const Season& getSeasons() const;

    private:
        void loadLevel();

        LevelInfo info;
        LevelConfig config;

        Animal animals;
        Event events;
        Plant plants;
        Season seasons;
};