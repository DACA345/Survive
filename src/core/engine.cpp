#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

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
    affectBars(food.effect); \
    if (food.edible) { \
       result.message = QString("You ate %1: %2. It made you feel better").arg(food.name).arg(food.name); \
    } else { \
        result.message = QString("You ate %1: %2. It made you feel awful").arg(food.category).arg(food.name); \
    }

Engine::Engine(const QString& levelId, const int& seed)
    : level(levelId),
        energyBar(BAR_MAX),
        hungerBar(BAR_MAX),
        thirstBar(BAR_MAX),
        healthBar(BAR_MAX),
        moraleBar(BAR_MAX),
        climate(level.getConfig().optimumMinTemp, level.getConfig().optimumMaxTemp)
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
    : level(engine.level), random(engine.random)
{
    day = new Day(*engine.day);
    journal = engine.journal;
    energyBar = engine.energyBar;
    hungerBar = engine.hungerBar;
    thirstBar = engine.thirstBar;
    healthBar = engine.healthBar;
    moraleBar = engine.moraleBar;
    turns = engine.turns;
}

Engine Engine::loadFromFile(const QString& filePath)
{
    QFile jsonFile(filePath);

    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qFatal("Engine::Engine could not open file %s", filePath.toStdString().c_str());
    }

    QByteArray jsonData = jsonFile.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(jsonData));

    if (doc.isNull() || !doc.isObject())
    {
        qFatal("Engine::Engine could not parse json file %s", filePath.toStdString().c_str());
    }

    QJsonObject dump = doc.object();

    Engine engine = Engine(dump["level"].toString());
    engine.turns = dump["turns"].toInt();

    delete engine.day;
    engine.day = new Day(engine.getLevel().file("climate.json").toStdString(), dump["day"].toInt());

    engine.healthBar = Bar(dump["health"].toInt());
    engine.hungerBar = Bar(dump["hunger"].toInt());
    engine.thirstBar = Bar(dump["thirst"].toInt());
    engine.energyBar = Bar(dump["energy"].toInt());

    engine.journal = Journal();

    QJsonArray journalDump = dump["journal"].toArray();

    for (int i = 0; i < journalDump.size(); i++)
    {
        QJsonObject dayEntry = journalDump.at(i).toObject();

        int day = dayEntry["day"].toInt();

        engine.journal.addDay(day, dayEntry["event"].toString());

        QJsonArray actionEntries = dayEntry["actions"].toArray();

        for (int j = 0; j < actionEntries.size(); j++)
        {
            QJsonObject action = actionEntries.at(j).toObject();

            ActionEntry actionEntry;
            actionEntry.action = action["action"].toString();
            actionEntry.result = action["result"].toString();

            engine.journal.addEntry(day, actionEntry);
        }
    }

    jsonFile.close();

    return engine;
}

void Engine::dump(const QString& filePath)
{
    QJsonObject dump;

    dump["level"] = level.getInfo().id;
    dump["turns"] = turns;
    dump["day"] = day->currentDay();
    dump["health"] = healthBar.getValue();
    dump["hunger"] = hungerBar.getValue();
    dump["thirst"] = thirstBar.getValue();
    dump["energy"] = energyBar.getValue();
    dump["morale"] = moraleBar.getValue();

    QJsonArray journalArray = QJsonArray();

    for (int i = 1; i < journal.getDayCount() + 1; i++)
    {
        const DayEntry& entry = journal.getEntry(i);

        QJsonObject dayEntry;
        dayEntry["day"] = i;
        dayEntry["event"] = entry.dayEvent;

        QJsonArray actionEntries;

        for (const ActionEntry& actionEntry : entry.entries)
        {
            QJsonObject action;
            action["action"] = actionEntry.action;
            action["result"] = actionEntry.result;

            actionEntries.append(action);
        }

        dayEntry["actions"] = actionEntries;
        journalArray.append(dayEntry);
    }

    dump["journal"] = journalArray;

    QJsonDocument save;
    save.setObject(dump);


    QFileInfo fileInfo(filePath);
    QDir dir;

    if (!dir.exists(fileInfo.path()))
    {
        dir.mkpath(fileInfo.path());
    }


    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug("Engine::dump failed to open file %s", filePath.toStdString().c_str());
        return;
    }

    QByteArray jsonData = save.toJson(QJsonDocument::Indented);
    file.write(jsonData);
    file.close();
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
            result.message = "You drank clean water. You feel refreshed";
        }
        else
        {
            healthBar.minus(config.waterPoison);
            result.message = "You drank dirty water. You feel awful";
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
    updateTemp(*day);
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

void Engine::updateTemp(Day day)
{
    const ClimateData& climate = day.getCurrentClimateData();

    nightTemp = day.getRandomTemperatureValue(climate.minTemperature);
    dayTemp = day.getRandomTemperatureValue(climate.avgTemperature);
    afternoonTemp = day.getRandomTemperatureValue(climate.maxTemperature);
    // double rainVal = day.getRandomPrecipitationValue(climate.precipitation);
}

void Engine::affectBars(Effect effect)
{
    // For now multiplier might be optimized
    double cMulti = climate.optimum(nightTemp, afternoonTemp) ? level.getConfig().climateMulti : 1; // Climate Multiplier
    
    double mMulti = 1; // Morale Multiplier
    if (moraleBar.getValue() > level.getConfig().optimumMorale)
    {
        mMulti = level.getConfig().moraleMulti;
    }
    double multiplier = cMulti * mMulti;

    double flippedMulti = 1.0 / multiplier;

    // HealthBar
    healthBar.plus((effect.healthBar < 0) ? effect.healthBar * multiplier : effect.healthBar * flippedMulti);

    // ThirstBar
    thirstBar.plus((effect.thirstBar < 0) ? effect.thirstBar * multiplier : effect.thirstBar * flippedMulti);

    // HungerBar
    hungerBar.plus((effect.hungerBar < 0) ? effect.hungerBar * multiplier : effect.hungerBar * flippedMulti);

    // MoraleBar
    moraleBar.plus((effect.moraleBar < 0) ? effect.moraleBar * multiplier : effect.moraleBar * flippedMulti);

    // EnergyBar
    energyBar.plus((effect.energyBar < 0) ? effect.energyBar * multiplier : effect.energyBar * flippedMulti);
}

Engine::~Engine()
{
    delete day;
}
