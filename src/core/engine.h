#pragma once

#include <QRandomGenerator>

#include "bar.h"
#include "day.h"
#include "level.h"

#define ENGINE_INITIAL_TURNS 5

/**
 * @brief   This enum describes the results of an action
 * 
 */
enum class ActionBaseResult
{
    NO_TURNS,
    USED_TURNS,
    GAME_OVER,
    SUCCESS
};

/**
 * @brief   This struct contain the result and message of an action
 * 
 */
struct ActionResult
{
    ActionBaseResult result;
    QString message;
};

/**
 * @brief   This struct contain the Event Info of and also if it's triggered of an event
 * 
 */
struct EventResult
{
    const EventInfo& event;
    bool triggered;
};

/**
 * @brief   This class describes the engine instance
 * 
 */
class Engine
{
    public:
        Engine(const QString& levelId);
        ~Engine();

        static double probability();
        static bool chance(double probability);

        const Day& getDay() const;
        const Level& getLevel() const;

        ActionResult findFood();
        ActionResult findWater();
        ActionResult explore();
        ActionResult rest();

        EventResult nextDay();

        short getTurns() const;

        int getEnergy() const;
        int getHunger() const;
        int getThirst() const;
        int getHealth() const;

    private:
        static QRandomGenerator random;

        EventResult triggerDayEvent();

        short turns = ENGINE_INITIAL_TURNS;


        // Player bars
        Bar energyBar;
        Bar hungerBar;
        Bar thirstBar;
        Bar healthBar;
        Bar moraleBar;

        Day* day;

        Level level;
};