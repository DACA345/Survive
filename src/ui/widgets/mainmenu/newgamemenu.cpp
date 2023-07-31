#include <QDirIterator>

#include "newgamemenu.h"
#include "../../../config/files.h"

NewGameMenu::NewGameMenu(QWidget* parent)
    : ScalableWidget(parent)
{
    QDirIterator leveliterator(LEVEL_FOLDER, QDir::Dirs | QDir::NoDotAndDotDot);

    while (leveliterator.hasNext())
    {
        QDir levelDir(leveliterator.next());
        QString levelJsonPath = levelDir.filePath("level.json");
        if (QFile::exists(levelJsonPath))
        {
            levels.append(levelJsonPath);
        }
    }
}

NewGameMenu::~NewGameMenu()
{

}