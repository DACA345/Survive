#pragma once

#include <QString>

#include "animal.h"
#include "plant.h"
#include "event.h"

#include <QDebug>

struct LevelInfo
{
    QString id;
    QString name;
};

class Level
{
    public:
        Level(const QString& id);
        ~Level();

        QString file(const QString& name) const;
        
        const LevelInfo& getInfo() const;

    private:
        void loadLevel();

        LevelInfo info;

        Animal animals;
        Plant plants;
        Event disasters;
};