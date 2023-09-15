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
        /**
         * @brief      Constructs a new game instance.
         *
         * @param[in]  levelId  The level identifier
         * @param      parent   The parent
         */
        explicit Game(const QString& levelId, QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~Game();

    signals:
        /**
         * @brief      Returns to the main menu.
         */
        void returnToMenu();

    private slots:
        /**
         * @brief      Called on find food.
         */
        void onFindFood();

        /**
         * @brief      Called on find water.
         */
        void onFindWater();

        /**
         * @brief      Called on explore.
         */
        void onExplore();

        /**
         * @brief      Called on rest.
         */
        void onRest();

        /**
         * @brief      Called when the user has acknowledged the result.
         */
        void onResultAcknowledged();

        /**
         * @brief      Called when the user sleeps.
         */
        void nextDay();

    private:
        /**
         * @brief      Paint event handler. See QWidget paint.
         *
         * @param      event  The event
         */
        void paintEvent(QPaintEvent* event) override;

        /**
         * @brief      Loads the widgets graphics.
         */
        void loadGraphics();

        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        /**
         * @brief      Update the bar elements.
         */
        void updateBars();

        /**
         * @brief      Update the UI.
         */
        void updateUi();

        /**
         * @brief      Gets a texture files path.
         *
         * @param[in]  name  The file name
         *
         * @return     The string.
         */
        QString textureFile(const QString& name);

        /**
         * @brief      Handles the result of a user's action.
         *
         * @param[in]  result  The result
         */
        void handleActionResult(ActionResult result);

        /**
         * @brief      Ends the game.
         */
        void endGame();

        /**
         * Game engine.
         */
        Engine engine;

        // Ui elements
        NotebookWidget* notebookWidget;
        GameOver* gameOver;

        SVGPushButton* notebookButton;

        QSvgWidget* bars;
        QSvgWidget* healthBarFill;
        QSvgWidget* thirstBarFill;
        QSvgWidget* hungerBarFill;
        QSvgWidget* energyBarFill;

        QPixmap background;
};
