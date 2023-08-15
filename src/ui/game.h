#pragma once
#include <QLabel>
#include <QPushButton>
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

    private slots:
        void onFindFood();
        void onFindWater();
        void onExplore();
        void onRest();

    private:
        void paintEvent(QPaintEvent* event) override;

        QString textureFile(const QString& name);

        void loadGraphics();

        void setupUi();
        void updateUi();

        Engine engine;

        // Ui elements
        QPushButton* findFoodButton;
        QPushButton* findWaterButton;
        QPushButton* exploreButton;
        QPushButton* restButton;

        QLabel* energyLabel;
        QLabel* hungerLabel;
        QLabel* thirstLabel;
        QLabel* healthLabel;

        QPixmap background;
};
