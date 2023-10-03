#include <QApplication>

#include "mainmenu.h"

MainMenu::MainMenu(QWidget* parent)
    : ScalableWidget(parent)
{
    // Fill the whole parent
    resize(parent->size());

    menu = new Menu(this);

    // Setup connections for switching between menus
    connect(menu, &Menu::newGameMenuOpened, this, &MainMenu::displayNewGameMenu);
    connect(menu, &Menu::loadGameMenuOpened, this, &MainMenu::displayLoadGameMenu);
    connect(menu, &Menu::settingsMenuOpened, this, &MainMenu::displaySettingsMenu);

    // Display the main menu
    addWidget(menu, 0, 0, 1, 1);
}

void MainMenu::onNewGameButtonClicked(const QString& id)
{
    emit newGameButtonClicked(id);

    closeNewGameMenu();
}

void MainMenu::displayNewGameMenu()
{
    newGameMenu = new NewGameMenu(this);

    // Setup connections
    connect(newGameMenu, &NewGameMenu::newGameMenuClosed, this, &MainMenu::closeNewGameMenu);
    connect(newGameMenu, &NewGameMenu::levelSelected, this, &MainMenu::onNewGameButtonClicked);

    // Display the new game menu
    addWidget(newGameMenu, 0, 0, 1, 1);

    newGameMenu->show();
    menu->hide();
}

void MainMenu::closeNewGameMenu()
{
    menu->show();
    newGameMenu->hide();
    removeWidget(newGameMenu);

    delete newGameMenu;
}

void MainMenu::displayLoadGameMenu()
{
    loadGameMenu = new LoadGameMenu(this);

    // Setup connections
    connect(loadGameMenu, &LoadGameMenu::loadGameMenuClosed, this, &MainMenu::closeLoadGameMenu);
    connect(loadGameMenu, &LoadGameMenu::saveSelected, this, &MainMenu::onSaveSelected);

    // Display the load game menu
    addWidget(loadGameMenu, 0, 0, 1, 1);

    loadGameMenu->show();
    menu->hide();
}

void MainMenu::onSaveSelected(const QString& id)
{
    emit saveGameSelected(id);

    closeLoadGameMenu();
}

void MainMenu::closeLoadGameMenu()
{
    menu->show();
    loadGameMenu->hide();
    removeWidget(loadGameMenu);

    delete loadGameMenu;
}

void MainMenu::displaySettingsMenu()
{
    settingsMenu = new SettingsMenu(this);

    // Setup connections
    connect(settingsMenu, &SettingsMenu::resolutionOptionChanged, this, &MainMenu::uiOptionChanged);
    connect(settingsMenu, &SettingsMenu::frameOptionChanged, this, &MainMenu::uiOptionChanged);
    connect(settingsMenu, &SettingsMenu::settingsMenuClosed, this, &MainMenu::closeSettingsMenu);

    // Display the settings menu
    addWidget(settingsMenu, 0, 0, 1, 1);

    settingsMenu->show();
    menu->hide();
}

void MainMenu::closeSettingsMenu()
{
    menu->show();
    settingsMenu->hide();
    removeWidget(settingsMenu);

    delete settingsMenu;
}

MainMenu::~MainMenu()
{

}