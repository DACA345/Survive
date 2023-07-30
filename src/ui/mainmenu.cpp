#include <QApplication>

#include "mainmenu.h"

MainMenu::MainMenu(QWidget* parent)
    : ScalableWidget(parent)
{
    // Fill the whole parent
    resize(parent->size());

    menu = new Menu(this);

    // Setup connections for switching between menus
    connect(menu, &Menu::settingsMenuOpened, this, &MainMenu::displaySettingsMenu);

    // Display the main menu
    addWidget(menu, 0, 0, 1, 1);
}

void MainMenu::onUiOptionChanged()
{
    emit uiOptionChanged();
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
    delete menu;
}