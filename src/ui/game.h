#pragma once
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QSvgWidget>

#include "widgets/scalablewidget.h"
#include "widgets/svgpushbutton.h"
#include "widgets/game/gameover.h"
#include "widgets/game/notebook/notebookwidget.h"
#include "../core/engine.h"

/**
 * @brief      This class describes the game instance.
 */
class Game : public ScalableWidget
{
    Q_OBJECT

    public:
        explicit Game(const QString& levelId, QWidget *parent = nullptr);
        ~Game();

    signals:
        void returnToMenu();

    private slots:
        void onFindFood();
        void onFindWater();
        void onExplore();
        void onRest();

        void onResultAcknowledged();

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
        NotebookWidget* notebookWidget;
        GameOver* gameOver = nullptr;

        SVGPushButton* notebookButton;

        QPushButton* sleepButton;

        QSvgWidget* bars;
        QSvgWidget* healthBarFill;
        QSvgWidget* thirstBarFill;
        QSvgWidget* hungerBarFill;
        QSvgWidget* energyBarFill;

        QPixmap background;
};
