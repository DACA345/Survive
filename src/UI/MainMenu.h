#pragma once
#include <QPushButton>

#include "Widgets/ScalableWidget.h"

class MainMenu : public ScalableWidget
{
    Q_OBJECT;

    public:
        MainMenu(QWidget* parent);
        ~MainMenu();

    private:
        void setupUi();

        // Ui attributes
        QPushButton* newGameButton;
        QPushButton* loadGameButton;
        QPushButton* settingsButton;
        QPushButton* exitButton;
};