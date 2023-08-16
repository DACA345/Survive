#pragma once

#include <QString>

#include "animal.h"
#include "plant.h"
#include "event.h"

#include <QDebug>

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

    // Water
    double findWaterNothing = 0.2;

    // Day events
    double disaster = 0.02;
};

class Level
{
    public:
        Level(const QString& id);
        ~Level();

        QString file(const QString& name) const;
        
        const LevelInfo& getInfo() const;
        const LevelConfig& getConfig() const;

    private:
        void loadLevel();

        LevelInfo info;
        LevelConfig config;

        Animal animals;
        Plant plants;
        Event disasters;
};