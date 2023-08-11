#pragma once
#include <QPushButton>
#include <QLabel>

#include "widgets/mainmenu/newgamemenu.h"
#include "widgets/mainmenu/loadgamemenu.h"
#include "widgets/mainmenu/settingsmenu.h"
#include "widgets/mainmenu/menu.h"

class MainMenu : public ScalableWidget
{
    Q_OBJECT

    public:
        MainMenu(QWidget* parent = nullptr);
        ~MainMenu();

    signals:
        void newGameButtonClicked(const QString& id);

        void uiOptionChanged();

    public slots:
        void onNewGameButtonClicked(const QString& id);

        void onUiOptionChanged();

        void displayNewGameMenu();
        void closeNewGameMenu();

        void displayLoadGameMenu();
        void closeLoadGameMenu();

        void displaySettingsMenu();
        void closeSettingsMenu();

    private:

        // Main Menu widgets
        NewGameMenu* newGameMenu;
        LoadGameMenu* loadGameMenu;
        SettingsMenu* settingsMenu;
        Menu* menu;
};