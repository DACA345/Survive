#pragma once

#include "bar.h"
#include "day.h"
#include "level.h"

#define ENGINE_INITIAL_TURNS 5

enum class ActionResult
{
    NO_TURNS,
    USED_TURNS,
    GAME_OVER,
    SUCCESS
};

class Engine
{
public:
    Engine(const QString& levelId);
    ~Engine();

    const Level& getLevel() const;

    ActionResult findFood();
    ActionResult findWater();
    ActionResult explore();
    ActionResult rest();

    void nextDay();

    short getTurns() const;

    int getEnergy() const;
    int getHunger() const;
    int getThirst() const;
    int getHealth() const;

private:
    short turns = ENGINE_INITIAL_TURNS;

    // Player bars
    Bar energyBar;
    Bar hungerBar;
    Bar thirstBar;
    Bar healthBar;

    Day* day;

    Level level;
};