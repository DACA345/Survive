#pragma once
#include <QPushButton>
#include <QLabel>

#include "Widgets/ScalableWidget.h"
#include "Widgets/MainMenu/SettingsMenu.h"

class MainMenu : public ScalableWidget
{
    Q_OBJECT;

    public:
        MainMenu(QWidget* parent);
        ~MainMenu();

    private slots:

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