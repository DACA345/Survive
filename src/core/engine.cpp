#include "engine.h"
#include "engine.h"
#include "../config/files.h"

#define HANDLE_ACTION_INITIAL \
    if (turns == 0) \
        return ActionResult::NO_TURNS; \
    else if (turns == 1 && turns--) \
        return ActionResult::USED_TURNS; \
    turns--;

#define HANDLE_ACTION_FINAL \
    if (energyBar.isEmpty() || hungerBar.isEmpty() || thirstBar.isEmpty() || healthBar.isEmpty()) \
        return ActionResult::GAME_OVER; \
    return ActionResult::SUCCESS; \

Engine::Engine(const QString& levelId)
    : level(levelId),
        energyBar(BAR_MAX),
        hungerBar(BAR_MAX),
        thirstBar(BAR_MAX),
        healthBar(BAR_MAX)
{
    day = new Day(level.file("climate.json").toStdString());
}

double Engine::probability()
{
    return random.generateDouble();
}

bool Engine::chance(double probability)
{
    return this->probability() <= probability;
}

const Level& Engine::getLevel() const
{
    return level;
}

ActionResult Engine::findFood()
{
    HANDLE_ACTION_INITIAL

    energyBar.minus(10);
    hungerBar.plus(10);
    thirstBar.plus(5);
    healthBar.plus(5);

    HANDLE_ACTION_FINAL
}

ActionResult Engine::findWater()
{
    HANDLE_ACTION_INITIAL

    energyBar.plus(10);
    hungerBar.plus(5);
    thirstBar.plus(10);
    healthBar.plus(5);

    HANDLE_ACTION_FINAL
}

ActionResult Engine::explore()
{
    HANDLE_ACTION_INITIAL

    energyBar.minus(20);
    hungerBar.plus(10);
    thirstBar.minus(10);
    healthBar.minus(5);

    HANDLE_ACTION_FINAL
}

ActionResult Engine::rest()
{
    HANDLE_ACTION_INITIAL

    energyBar.plus(20);
    hungerBar.minus(10);
    thirstBar.minus(10);
    healthBar.plus(5);

    HANDLE_ACTION_FINAL
}

void Engine::nextDay()
{
    turns = ENGINE_INITIAL_TURNS;
    day->nextDay();
}

short Engine::getTurns() const
{
    return turns;
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