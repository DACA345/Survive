#pragma once
#include <QWidget>

#include "widgets/scalablewidget.h"

/**
 * @brief      This class describes the game instance.
 */
class Game : public ScalableWidget
{
    Q_OBJECT

    public:
        Game(const QString& levelId, QWidget *parent = nullptr);
        ~Game();

    private:
};
