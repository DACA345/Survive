#pragma once
#include "Level.h"

class Engine
{
public:
    Engine(Level& level);
    ~Engine();

private:
    int day;
    Level* level;
};