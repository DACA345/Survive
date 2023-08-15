#include "engine.h"
#include "../config/files.h"

Engine::Engine(const QString& levelId)
    : level(levelId), energyBar(100), hungerBar(100), thirstBar(100), healthBar(100)
{
    day = new Day(level.file("climate.json").toStdString());
}

const Level& Engine::getLevel() const
{
    return level;
}

void Engine::findFood()
{
    energyBar.minus(10);
    hungerBar.plus(10);
    thirstBar.plus(5);
    healthBar.plus(5);
}

void Engine::findWater()
{
    energyBar.plus(10);
    hungerBar.plus(5);
    thirstBar.plus(10);
    healthBar.plus(5);
}

void Engine::explore()
{
    energyBar.minus(20);
    hungerBar.plus(10);
    thirstBar.minus(10);
    healthBar.minus(5);
}

void Engine::rest()
{
    energyBar.plus(20);
    hungerBar.minus(10);
    thirstBar.minus(10);
    healthBar.plus(5);
}

int Engine::getEnergy() const
{
    return energyBar.getValue();
}

int Engine::getHunger() const
{
    return hungerBar.getValue();
}

int Engine::getThirst() const
{
    return thirstBar.getValue();
}

int Engine::getHealth() const
{
    return healthBar.getValue();
}

Engine::~Engine()
{
    delete day;
}
