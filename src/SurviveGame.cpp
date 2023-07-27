#include "SurviveGame.h"

SurviveGame::SurviveGame(QWidget* parent)
    : QMainWindow(parent)
{
}

void SurviveGame::resizeEvent(QResizeEvent* event)
{
    if (!windowSizeInitialized)
    {
        setupUi();
    }

    windowSizeInitialized = true;
    QMainWindow::resizeEvent(event);
}

void SurviveGame::setupUi()
{
    mainMenu = new MainMenu(this);
    setCentralWidget(mainMenu);
}

SurviveGame::~SurviveGame()
{
    delete mainMenu;
}