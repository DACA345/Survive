#pragma once
#include <QMainWindow>

#include "ui/mainmenu.h"
#include "ui/game.h"

/**
 * @brief      This class describes the base main window of the game.
 */
class SurviveGame : public QMainWindow
{
    Q_OBJECT

    public:
        /**
         * @brief      Create a new main window.
         *
         * @param      parent  The parent
         */
        explicit SurviveGame(QWidget* parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~SurviveGame();

    private slots:
        /**
         * @brief      Called when a new game is selected.
         *
         * @param[in]  id    The identifier of the level
         */
        void onNewGame(const QString& id);

        void onReturnToMenu();

    private:
        /**
         * @brief      Resize event handler.
         *
         * @param      event  The event
         */
        void resizeEvent(QResizeEvent* event) override;

        /**
         * @brief      Sets up the UI based on the user settings.
         */
        void setupUiSettings();

        /**
         * @brief      Set up the main window UI.
         */
        void setupUi();
        
        /**
         * Main menu for the game.
         */
        MainMenu* mainMenu;

        /**
         * Game instance.
         */
        Game* game;

        bool windowSizeInitialized = false;
};