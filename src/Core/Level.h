#pragma once
#include <QString>

struct LevelInfo
{
    QString name;
};

class Level
{
    public:
        Level(QString name);
        ~Level();

    protected:
        virtual void setActions() = 0;

    private:
        LevelInfo info;
};