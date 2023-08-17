#include "level.h"
#include "level.h"
#include "level.h"
#include "level.h"
#include <QJsonDocument>
#include <QJsonObject>

#include "level.h"
#include "../config/files.h"

Level::Level(const QString& id)
    : info{ id }, animals(file("animals.json")), plants(file("plants.json")), disasters(file("disaster_ev.json"))
{
    loadLevel();
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

const Plant& Level::getPlants() const
{
    return plants;
}

const Event& Level::getDisasters() const
{
    return disasters;
}

void Level::loadLevel()
{
    QFile levelFile(file("level.json"));
    levelFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonDocument levelDoc = QJsonDocument::fromJson(levelFile.readAll());
    info.name = levelDoc.object()["title_name"].toString();
    levelFile.close();
}

Level::~Level()
{
}
