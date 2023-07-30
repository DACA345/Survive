#pragma once
#include <QPushButton>
#include <QLabel>

#include "widgets/scalablewidget.h"
#include "widgets/mainmenu/settingsmenu.h"

class MainMenu : public ScalableWidget
{
    Q_OBJECT;

    public:
        MainMenu(QWidget* parent);
        ~MainMenu();

    private slots:
        void displaySettingsMenu();
        void closeSettingsMenu();

    private:
        void setupUi();

        // Ui attributes
        QLabel* menuTitle;

        QPushButton* newGameButton;
        QPushButton* loadGameButton;
        QPushButton* settingsButton;
        QPushButton* exitButton;

        // Main Menu widgets
        SettingsMenu* settingsMenu;
};