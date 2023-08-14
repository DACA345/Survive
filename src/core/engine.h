#pragma once
#include "level.h"

class Engine
{
public:
    Engine(Level& level);
    ~Engine();

private:
    int day;
    Level* level;
};