#pragma once
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QSvgWidget>

#include "widgets/scalablewidget.h"
#include "widgets/game/resultwidget.h"
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

    private slots:
        void onFindFood();
        void onFindWater();
        void onExplore();
        void onRest();

        void nextDay();

    private:
        void paintEvent(QPaintEvent* event) override;

        void loadGraphics();
        void setupUi();
        void updateBars();
        void updateUi();

        QString textureFile(const QString& name);

        void handleActionResult(ActionResult result);
        void endGame();

        Engine engine;

        // Ui elements
        ResultWidget* resultWidget;

        QPushButton* findFoodButton;
        QPushButton* findWaterButton;
        QPushButton* exploreButton;
        QPushButton* restButton;
        QPushButton* sleepButton;

        QSvgWidget* bars;
        QSvgWidget* healthBarFill;
        QSvgWidget* thirstBarFill;
        QSvgWidget* hungerBarFill;
        QSvgWidget* energyBarFill;

        QPixmap background;
};
