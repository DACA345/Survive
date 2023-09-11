#pragma once

#include <QRandomGenerator>

#include "bar.h"
#include "day.h"
#include "level.h"
#include "journal.h"

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
    QString action;
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
        /**
         * @brief      Construct a new engine instance from a level id.
         *
         * @param[in]  levelId  The level identifier
         */
        Engine(const QString& levelId);

        /**
         * @brief      Destroys the object.
         */
        ~Engine();

        /**
         * @brief      Generates a random double between 0, 1.
         *
         * @return     Random double between 0, 1/
         */
        static double probability();

        /**
         * @brief      Determine if a probability will hit.
         *
         * @param[in]  probability  The probability
         *
         * @return     True if probability was reached, false otherwise.
         */
        static bool chance(double probability);

        /**
         * @brief      Gets the day.
         *
         * @return     The day.
         */
        const Day& getDay() const;

        /**
         * @brief      Gets the level.
         *
         * @return     The level.
         */
        const Level& getLevel() const;

        /**
         * @brief      Gets the journal.
         *
         * @return     The journal.
         */
        const Journal& getJournal() const;

        /**
         * @brief      Action for finding food.
         *
         * @return     The action result.
         */
        ActionResult findFood();

        /**
         * @brief      Action for finding water.
         *
         * @return     The action result.
         */
        ActionResult findWater();

        /**
         * @brief      Action for exploring.
         *
         * @return     The action result.
         */
        ActionResult explore();

        /**
         * @brief      Action for resting.
         *
         * @return     The action result.
         */
        ActionResult rest();

        /**
         * @brief      Progress to the next day.
         *
         * @return     The event of the new day.
         */
        EventResult nextDay();

        /**
         * @brief      Gets the turns.
         *
         * @return     The turns.
         */
        short getTurns() const;

        /**
         * @brief      Gets the user's energy.
         *
         * @return     The energy.
         */
        int getEnergy() const;

        /**
         * @brief      Gets the user's hunger.
         *
         * @return     The hunger.
         */
        int getHunger() const;

        /**
         * @brief      Gets the user's thirst.
         *
         * @return     The thirst.
         */
        int getThirst() const;

        /**
         * @brief      Gets the user's health.
         *
         * @return     The health.
         */
        int getHealth() const;

    private:
        /**
         * The random generator.
         */
        static QRandomGenerator random;

        /**
         * @brief      Trigger the day's event.
         *
         * @return     The event result.
         */
        EventResult triggerDayEvent();

        /**
         * @brief      Apply effects on the user's bars.
         *
         * @param[in]  effect  The effects to apply.
         */
        void affectBars(Effect effect);

        /**
         * The current turns.
         */
        short turns = ENGINE_INITIAL_TURNS;


        /**
         * The energy bar.
         */
        Bar energyBar;

        /**
         * The hunger bar.
         */
        Bar hungerBar;

        /**
         * The thirst bar.
         */
        Bar thirstBar;

        /**
         * The health bar.
         */
        Bar healthBar;

        /**
         * The morale bar.
         */
        Bar moraleBar;

        /**
         * The current day.
         */
        Day* day;

        /**
         * The level.
         */
        Level level;

        /**
         * The journal.
         */
        Journal journal;
};