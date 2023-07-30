#pragma once
#include <QPushButton>
#include <QLabel>

#include "widgets/mainmenu/settingsmenu.h"
#include "widgets/mainmenu/menu.h"

class MainMenu : public ScalableWidget
{
    Q_OBJECT;

    public:
        MainMenu(QWidget* parent = nullptr);
        ~MainMenu();

    signals:
        void uiOptionChanged();

    public slots:
        void onUiOptionChanged();

        void displaySettingsMenu();
        void closeSettingsMenu();

    private:

        // Main Menu widgets
        SettingsMenu* settingsMenu;
        Menu* menu;
};