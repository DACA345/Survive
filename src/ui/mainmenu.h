#pragma once
#include <QPushButton>
#include <QLabel>

#include "widgets/mainmenu/newgamemenu.h"
#include "widgets/mainmenu/loadgamemenu.h"
#include "widgets/mainmenu/settingsmenu.h"
#include "widgets/mainmenu/menu.h"

/**
 * @brief      This class describes the game's main menu.
 */
class MainMenu : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Create a new main menu instance.
         *
         * @param      parent  The parent
         */
        MainMenu(QWidget* parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~MainMenu();

    signals:
        /**
         * @brief      Emitted when a new game button is clicked.
         *
         * @param[in]  id    The identifier
         */
        void newGameButtonClicked(const QString& id);

        /**
         * @brief      Emitted when a UI option is changed.
         */
        void uiOptionChanged();

    public slots:
        /**
         * @brief      Called when new game button clicked.
         *
         * @param[in]  id    The identifier
         */
        void onNewGameButtonClicked(const QString& id);

        /**
         * @brief      Called when a UI option changed.
         */
        void onUiOptionChanged();

        /**
         * @brief      Displays the new game menu.
         */
        void displayNewGameMenu();

        /**
         * @brief      Closes the new game menu.
         */
        void closeNewGameMenu();

        /**
         * @brief      Displays the load game menu.
         */
        void displayLoadGameMenu();

        /**
         * @brief      Closes the load game menu.
         */
        void closeLoadGameMenu();

        /**
         * @brief      Displays the settings menu.
         */
        void displaySettingsMenu();

        /**
         * @brief      Closes the settings menu.
         */
        void closeSettingsMenu();

    private:

        // Main Menu widgets
        NewGameMenu* newGameMenu;
        LoadGameMenu* loadGameMenu;
        SettingsMenu* settingsMenu;
        Menu* menu;
};