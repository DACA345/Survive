#include "SurviveGame.h"

SurviveGame::SurviveGame(QWidget* parent)
    : QMainWindow(parent)
{
    // TODO(Callum): Set to initial size of desktop
    // Then allow configuration in settings to different resolutions
    // Maybe hopefully allow them to resize accordingly if ScalableWidget is fixed.
    setFixedSize(800, 600);
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