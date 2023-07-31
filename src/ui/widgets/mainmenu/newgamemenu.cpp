#include <QDir>

#include "newgamemenu.h"
#include "../../../config/files.h"

const QDir levelsDir = QDir(LEVEL_FOLDER);

NewGameMenu::NewGameMenu(QWidget* parent)
    : ScalableWidget(parent)
{

}

NewGameMenu::~NewGameMenu()
{

}