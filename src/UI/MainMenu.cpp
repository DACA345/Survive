#include "MainMenu.h"

MainMenu::MainMenu(QWidget* parent)
    : ScalableWidget(parent)
{
    resize(parent->size());
    setupUi();
}

void MainMenu::setupUi()
{
    newGameButton = new QPushButton("New Game", this);
    loadGameButton = new QPushButton("Load Game", this);
    settingsButton = new QPushButton("Settings", this);
    exitButton = new QPushButton("Exit", this);

    addWidget(loadGameButton, 0, 0.8, 0.15, 0.05);
    addWidget(newGameButton, 0, 0.85, 0.15, 0.05);
    addWidget(settingsButton, 0, 0.9, 0.15, 0.05);
    addWidget(exitButton, 0, 0.95, 0.15, 0.05);
}

MainMenu::~MainMenu()
{
    delete newGameButton;
    delete loadGameButton;
    delete settingsButton;
    delete exitButton;
}