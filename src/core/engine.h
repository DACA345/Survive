#pragma once

#include "bar.h"
#include "day.h"
#include "level.h"

class Engine
{
public:
    Engine(const QString& levelId);
    ~Engine();

    const Level& getLevel() const;

    void findFood();
    void findWater();
    void explore();
    void rest();

    int getEnergy() const;
    int getHunger() const;
    int getThirst() const;
    int getHealth() const;

private:
    short turns = 5;

    // Player bars
    Bar energyBar;
    Bar hungerBar;
    Bar thirstBar;
    Bar healthBar;

    Day* day;

    Level level;
};