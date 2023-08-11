#pragma once
#include <QWidget>

#include "widgets/scalablewidget.h"

class Game : public ScalableWidget
{
    Q_OBJECT

    public:
        Game(const QString& levelId, QWidget *parent = nullptr);
        ~Game();

    private:
};
