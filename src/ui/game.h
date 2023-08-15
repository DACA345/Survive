#pragma once
#include <QWidget>

#include "widgets/scalablewidget.h"
#include "../core/engine.h"

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
        void paintEvent(QPaintEvent* event) override;

        QString textureFile(const QString& name);

        void loadGraphics();

        void setupUi();

        Engine engine;

        QPixmap background;
};
