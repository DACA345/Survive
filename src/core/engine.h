#pragma once

#include "level.h"
#include "day.h"

class Engine
{
public:
    Engine(const QString& levelId);
    ~Engine();

    const Level& getLevel() const;

private:
    Day* day;

    Level level;
};