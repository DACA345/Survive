#include "engine.h"
#include "engine.h"
#include "../config/files.h"

#define HANDLE_ACTION_INITIAL \
    const LevelConfig& config = level.getConfig(); \
    ActionResult result; \
    if (turns == 0) \
    { \
        result.result = ActionBaseResult::NO_TURNS; \
        return result; \
    } \
    turns--;

#define HANDLE_ACTION_FINAL(actionName) \
    done: \
        if (energyBar.isEmpty() || hungerBar.isEmpty() || thirstBar.isEmpty() || healthBar.isEmpty())\
        { \
            result.result = ActionBaseResult::GAME_OVER; \
            return result; \
        } \
        else \
        { \
            result.result = ActionBaseResult::SUCCESS; \
        } \
        result.action = actionName; \
        journal.addEntry(day->currentDay(), { actionName, result.message }); \
        return result;

#define FOUND_FOOD(type) \
    const type##Info& food = level.get##type##s().getRandom##type(); \
    result.message = QString("You have found %1: %2 and ate it.").arg( \
        food.category \
    ).arg(food.name); \
    affectBars(food.effect);

Engine::Engine(const QString& levelId, const int& seed)
    : level(levelId),
        energyBar(BAR_MAX),
        hungerBar(BAR_MAX),
        thirstBar(BAR_MAX),
        healthBar(BAR_MAX),
        moraleBar(BAR_MAX)
{
    if (seed == -1)
    {
        random = QRandomGenerator::securelySeeded();
    }
    else
    {
        random = QRandomGenerator(seed);
    }

    day = new Day(level.file("climate.json").toStdString());
    journal.addDay(day->currentDay());
}


Engine::Engine(const Engine& engine)
    : level(level.getInfo().id)
{
    random = engine.random;
    day = new Day(*engine.day);
    journal = engine.journal;
    energyBar = engine.energyBar;
    hungerBar = engine.hungerBar;
    thirstBar = engine.thirstBar;
    healthBar = engine.healthBar;
    moraleBar = engine.moraleBar;
    turns = engine.turns;
}

double Engine::probability()
{
    return random.generateDouble();
}

bool Engine::chance(double probability)
{
    return Engine::probability() <= probability;
}

bool Engine::isGameOver() const
{
    return energyBar.isEmpty() || hungerBar.isEmpty() || thirstBar.isEmpty() || healthBar.isEmpty();
}

const Level& Engine::getLevel() const
{
    return level;
}

const Day& Engine::getDay() const
{
    return *day;
}

const Journal& Engine::getJournal() const
{
    return journal;
}

ActionResult Engine::findFood()
{
    HANDLE_ACTION_INITIAL

    energyBar.minus(config.findFoodEnergy);
    if (chance(config.findFoodNothing))
    {
        result.message = "You found nothing.";
        goto done;
    }
    else
    {
        if (chance(config.findFoodAnimal))
        {
            FOUND_FOOD(Animal)
        }
        else
        {
            FOUND_FOOD(Plant)
        }
    }

    HANDLE_ACTION_FINAL("Find Food")
}

ActionResult Engine::findWater()
{
    HANDLE_ACTION_INITIAL

    energyBar.minus(config.findWaterEnergy);
    if (chance(config.findWaterNothing))
    {
        result.message = "You found nothing.";
        goto done;
    }
    else
    {
        thirstBar.plus(config.waterThirst);
        if (chance(config.findCleanWater))
        {
            result.message = "You have found clean water and drank it.";
        }
        else
        {
            healthBar.minus(config.waterPoison);
            result.message = "You have found dirty water and drank it.";
        }
    }

    HANDLE_ACTION_FINAL("Find Water")
}

ActionResult Engine::explore()
{
    HANDLE_ACTION_INITIAL

    hungerBar.minus(config.exploreHunger);
    thirstBar.minus(config.exploreThirst);

    if (chance(config.exploreNothing))
    {
        energyBar.minus(config.exploreNothingEnergy);
        result.message = "You explored the surrounding area but did not find anything.";
        goto done;
    }
    else
    {
        if (chance(config.exploreAnimal))
        {
            FOUND_FOOD(Animal)
        }
        else if (chance(config.explorePlant))
        {
            FOUND_FOOD(Plant)
        }
        else
        {
            const ExploreInfo& explore = level.getExplorer().getRandomExplore();

            energyBar.minus(config.exploreEnergy);
            result.message = QString("You %1 %2.").arg(explore.category).arg(explore.eventName);
        }
    }

    HANDLE_ACTION_FINAL("Explore")
}

ActionResult Engine::rest()
{
    HANDLE_ACTION_INITIAL

    energyBar.plus(config.restEnergy);
    hungerBar.minus(config.restHunger);
    thirstBar.minus(config.restThirst);

    if (hungerBar.getValue() > config.restHungerHeal && thirstBar.getValue() > config.restThirstHeal)
    {
        result.message = "You awake feeling healthier.";
        healthBar.plus(config.restWellHeal);
        goto done;
    }
    else
    {
        result.message = "You rested.";
        goto done;
    }

    HANDLE_ACTION_FINAL("Rest")
}

EventResult Engine::nextDay()
{
    turns = ENGINE_INITIAL_TURNS;

    // TODO(Callum): Actual sleep config
    // For now just rest to regain energy
    turns++;
    rest();

    day->nextDay();
    return triggerDayEvent();
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

EventResult Engine::triggerDayEvent()
{
    const LevelConfig& config = level.getConfig();

    const EventInfo& event = chance(config.seasonEvent) ? level.getEvents().getRandomEventForSeason(
        level.getSeasons().getSeason(
            day->monthId()
        )
    ) : level.getEvents().getRandomEvent();

    bool didTrigger = level.getSeasons().getSeason(day->monthId()) == event.season
        ? chance(config.seasonEventTrigger) : chance(config.eventTrigger);

    if (didTrigger)
    {
        affectBars(event.effect);

        journal.addDay(day->currentDay(), event.event);
    }
    else
    {
        journal.addDay(day->currentDay());
    }

    return { event, didTrigger };
}

void Engine::affectBars(Effect effect)
{
    healthBar.plus(effect.healthBar);
    thirstBar.plus(effect.thirstBar);
    hungerBar.plus(effect.hungerBar);
    moraleBar.plus(effect.moraleBar);
    energyBar.plus(effect.energyBar);
}

Engine::~Engine()
{
    delete day;
}