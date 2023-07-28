#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(QWidget* parent)
    : ScalableWidget(parent)
{
    settings = new QSettings();
}

SettingsMenu::~SettingsMenu()
{
    delete settings;
}