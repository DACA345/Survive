#include <QJsonDocument>
#include <QJsonObject>

#include "level.h"
#include "../config/files.h"

void populateLevelConfig(const QJsonObject& json, LevelConfig& config)
{
    if (json.contains("action_probabilities") && json["action_probabilities"].isObject())
    {
        QJsonObject actionProbJson = json["action_probabilities"].toObject();
        config.findFoodNothing = actionProbJson["find_food_nothing"].toDouble();
        config.findFoodAnimal = actionProbJson["find_food_animal"].toDouble();
        config.findFoodEnergy = actionProbJson["find_food_energy"].toInt();
        config.plantPoison = actionProbJson["plant_poison"].toInt();
        config.findWaterNothing = actionProbJson["find_water_nothing"].toDouble();
        config.findCleanWater = actionProbJson["find_clean_water"].toDouble();
        config.waterThirst = actionProbJson["water_thirst"].toInt();
        config.waterPoison = actionProbJson["water_poison"].toInt();
        config.findWaterEnergy = actionProbJson["find_water_energy"].toInt();
    }

    if (json.contains("rest") && json["rest"].isObject())
    {
        QJsonObject restJson = json["rest"].toObject();
        config.restHungerHeal = restJson["rest_hunger_heal"].toInt();
        config.restThirstHeal = restJson["rest_thirst_heal"].toInt();
        config.restEnergy = restJson["rest_energy"].toInt();
        config.restWellHeal = restJson["rest_well_heal"].toInt();
        config.restHunger = restJson["rest_hunger"].toInt();
        config.restThirst = restJson["rest_thirst"].toInt();
    }

    if (json.contains("explore") && json["explore"].isObject())
    {
        QJsonObject exploreJson = json["explore"].toObject();
        config.exploreNothing = exploreJson["explore_nothing"].toDouble();
        config.exploreAnimal = exploreJson["explore_animal"].toDouble();
        config.explorePlant = exploreJson["explore_plant"].toDouble();
        config.exploreHunger = exploreJson["explore_hunger"].toInt();
        config.exploreThirst = exploreJson["explore_thirst"].toInt();
        config.exploreNothingEnergy = exploreJson["explore_nothing_energy"].toInt();
        config.exploreEnergy = exploreJson["explore_energy"].toInt();
    }

    if (json.contains("events") && json["events"].isObject())
    {
        QJsonObject eventsJson = json["events"].toObject();
        config.seasonEvent = eventsJson["season_event"].toDouble();
        config.seasonEventTrigger = eventsJson["season_event_trigger"].toDouble();
        config.eventTrigger = eventsJson["event_trigger"].toDouble();
    }

    if (json.contains("climate") && json["climate"].isObject())
    {
        QJsonObject climateJson = json["climate"].toObject();
        config.climateMulti = climateJson["climate_multi"].toDouble();
        config.optimumMinTemp = climateJson["optimum_min_temp"].toDouble();
        config.optimumMaxTemp = climateJson["optimum_max_temp"].toDouble();
    }

    if (json.contains("morale") && json["morale"].isObject())
    {
        QJsonObject moraleJson = json["morale"].toObject();
        config.moraleMulti = moraleJson["morale_multi"].toDouble();
        config.optimumMorale = moraleJson["optimum_morale"].toDouble();
    }
}

Level::Level(const QString& id)
    : info{ id },
        animals(file("animals.json")),
        events(file("events.json")),
        explorer(file("explore.json")),
        plants(file("plants.json")),
        seasons(file("season.json"))
{
    loadLevel();
}

Level::Level(const Level& level)
    : info(level.info),
        config(level.config),
        animals(level.animals),
        events(level.events),
        explorer(level.explorer),
        plants(level.plants),
        seasons(level.seasons)
{
}

QString Level::file(const QString& name) const
{
    return LEVEL_FILE(QString("%1/%2").arg(info.id).arg(name));
}

const LevelInfo& Level::getInfo() const
{
    return info;
}

const LevelConfig& Level::getConfig() const
{
    return config;
}

const Animal& Level::getAnimals() const
{
    return animals;
}

const Event& Level::getEvents() const
{
    return events;
}

const Explore& Level::getExplorer() const
{
    return explorer;
}

const Plant& Level::getPlants() const
{
    return plants;
}

const Season& Level::getSeasons() const
{
    return seasons;
}

void Level::loadLevel()
{
    QFile levelFile(file("level.json"));
    levelFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonDocument levelDoc = QJsonDocument::fromJson(levelFile.readAll());

    QJsonObject levelConfig = levelDoc.object()["config"].toObject();

    info.name = levelDoc.object()["title_name"].toString();
    levelFile.close();

    populateLevelConfig(levelConfig, config);
}

Level::~Level()
{
}