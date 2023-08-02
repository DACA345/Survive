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

    levels.append("test.json");
    levels.append("test.json");
    levels.append("test.json");

    setupUi();
}

void NewGameMenu::onNewGameMenuClosed()
{
    emit newGameMenuClosed();
}

void NewGameMenu::displayLevels()
{
    levelsWidget = new QWidget(this);

    levelsLayout = new QGridLayout(levelsWidget);

    for (int i = 0; i < levels.size(); i++)
    {
        QPushButton* levelButton = new QPushButton(levels[i], this);
        levelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        levelButtons.append(levelButton);

        int row = i / columns;
        int col = i % columns;

        levelsLayout->addWidget(levelButton, row, col);

        //connect(levelButton, &QPushButton::clicked, this, [this, i]()
        //    {
        //    emit newGameMenuClosed();
        //    emit levelSelected(levels[i]);
        //});
    }

    levelsWidget->setLayout(levelsLayout);

    addWidget(levelsWidget, 0.1, 0.1, 0.8, 0.7);
}

void NewGameMenu::setupUi()
{
    displayLevels();

    backButton = new QPushButton("Back", this);

    // Setup connections
    connect(backButton, &QPushButton::clicked, this, &NewGameMenu::onNewGameMenuClosed);

    // Add widgets
    addWidget(backButton, 0.4, 0.85, 0.2, 0.1);
}

NewGameMenu::~NewGameMenu()
{
    for (QPushButton* levelButton : levelButtons)
    {
        delete levelButton;
    }

    delete levelsLayout;
    delete levelsWidget;
    delete backButton;
}