#include "engine.h"
#include "../config/files.h"

Engine::Engine(const QString& levelId)
    : level(levelId)
{
    day = new Day(level.file("climate.json"));
}

const Level& Engine::getLevel() const
{
    return level;
}

Engine::~Engine()
{
    delete day;
}
