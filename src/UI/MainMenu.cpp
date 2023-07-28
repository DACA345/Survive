#include <QApplication>

#include "MainMenu.h"

MainMenu::MainMenu(QWidget* parent)
    : ScalableWidget(parent)
{
    resize(parent->size());
    setupUi();

    settingsMenu = new SettingsMenu(this);
    delete settingsMenu;
}

void MainMenu::setupUi()
{
    // Create game title
    QFont titleFont = font();
    titleFont.setPointSize(32);

    menuTitle = new QLabel("DACA: Survive", this);
    menuTitle->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    menuTitle->setFont(titleFont);

    // Create buttons for main menu
    newGameButton = new QPushButton("New Game", this);
    loadGameButton = new QPushButton("Load Game", this);
    settingsButton = new QPushButton("Settings", this);
    exitButton = new QPushButton("Exit", this);

    // Specify the widgets should scale with the window
    addWidget(menuTitle, 0, 0, 1, 0.2);
    addWidget(newGameButton, 0, 0.6, 0.2, 0.1);
    addWidget(loadGameButton, 0, 0.7, 0.2, 0.1);
    addWidget(settingsButton, 0, 0.8, 0.2, 0.1);
    addWidget(exitButton, 0, 0.9, 0.2, 0.1);

    // Setup button signals
    connect(exitButton, &QPushButton::clicked, this, &QApplication::quit, Qt::QueuedConnection);
}

MainMenu::~MainMenu()
{;
    delete menuTitle;

    delete newGameButton;
    delete loadGameButton;
    delete settingsButton;
    delete exitButton;
}