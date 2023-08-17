#pragma once

#include <QRandomGenerator>

#include "bar.h"
#include "day.h"
#include "level.h"

#define ENGINE_INITIAL_TURNS 5

enum class ActionBaseResult
{
    NO_TURNS,
    USED_TURNS,
    GAME_OVER,
    SUCCESS
};

struct ActionResult
{
    ActionBaseResult result;
    QString message;
};

class Engine
{
    public:
        Engine(const QString& levelId);
        ~Engine();

        double probability();
        bool chance(double probability);

        const Level& getLevel() const;

        ActionResult findFood();
        ActionResult findWater();
        ActionResult explore();
        ActionResult rest();

        EventInfo nextDay();

        short getTurns() const;

        int getEnergy() const;
        int getHunger() const;
        int getThirst() const;
        int getHealth() const;

    private:
        EventInfo triggerDayEvent();

        short turns = ENGINE_INITIAL_TURNS;

        QRandomGenerator random = QRandomGenerator::securelySeeded();

        // Player bars
        Bar energyBar;
        Bar hungerBar;
        Bar thirstBar;
        Bar healthBar;

        Day* day;

        Level level;
};