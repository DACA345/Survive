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
    else if (turns == 1) {\
        result.result = ActionBaseResult::USED_TURNS; \
    } \
    turns--;

#define HANDLE_ACTION_FINAL(action) \
    done: \
        if (energyBar.isEmpty() || hungerBar.isEmpty() || thirstBar.isEmpty() || healthBar.isEmpty())\
        { \
            result.result = ActionBaseResult::GAME_OVER; \
            return result; \
        } \
        result.result = ActionBaseResult::SUCCESS; \
        return result;

#define FOUND_FOOD(type) \
    const type##Info& food = level.get##type##s().getRandom##type(); \
    result.message = QString("You have found %1: %2 and ate it.").arg( \
        food.category \
    ).arg(food.name); \
    affectBars(food.effect);

QRandomGenerator Engine::random = QRandomGenerator::securelySeeded();

Engine::Engine(const QString& levelId)
    : level(levelId),
        energyBar(BAR_MAX),
        hungerBar(BAR_MAX),
        thirstBar(BAR_MAX),
        healthBar(BAR_MAX),
        moraleBar(BAR_MAX)
{
    day = new Day(level.file("climate.json").toStdString());
}

double Engine::probability()
{
    return random.generateDouble();
}

bool Engine::chance(double probability)
{
    return Engine::probability() <= probability;
}

const Level& Engine::getLevel() const
{
    return level;
}

const Day& Engine::getDay() const
{
    return *day;
}

ActionResult Engine::findFood()
{
    HANDLE_ACTION_INITIAL

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
    if (hungerBar.getValue() > config.restHungerHeal && thirstBar.getValue() > config.restThirstHeal)
    {
        result.message = "You awake feeling healthier.";
        healthBar.plus(config.restHealth);
    }
    else
    {
        result.message = "You rested.";
    }

    HANDLE_ACTION_FINAL("Rest")
}

EventResult Engine::nextDay()
{
    turns = ENGINE_INITIAL_TURNS;
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

    }
    else
    {
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