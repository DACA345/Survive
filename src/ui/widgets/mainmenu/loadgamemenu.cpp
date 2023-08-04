#include <QDirIterator>

#include "loadgamemenu.h"
#include "../../../config/files.h"

LoadGameMenu::LoadGameMenu(QWidget* parent)
    : ScalableWidget(parent)
{
    QDirIterator savesIterator(SAVE_FOLDER, QDir::Dirs | QDir::NoDotAndDotDot);

    while (savesIterator.hasNext())
    {
        QDir saveDir(savesIterator.next()); 
        QString saveJsonPath = saveDir.filePath("save.json");
        if (QFile::exists(saveJsonPath))
        {
            saves.append(saveJsonPath);
        }
    }

    setupUi();
}

void LoadGameMenu::onLoadGameMenuClosed()
{
    emit loadGameMenuClosed();
}

void LoadGameMenu::displaySaves()
{
    savesWidget = new QWidget(this);

    savesLayout = new QGridLayout(savesWidget);

    for (int i = 0; i < saves.size(); i++)
    {
        QPushButton* saveButton = new QPushButton(saves[i], this);
        saveButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        saveButtons.append(saveButton);

        int row = i / columns;
        int col = i % columns;

        savesLayout->addWidget(saveButton, row, col);

        //connect(saveButton, &QPushButton::clicked, this, [this, i]()
        //    {
        //    emit loadGameMenuClosed();
        //    emit saveSelected(saves[i]);
        //});
    }
    savesWidget->setLayout(savesLayout);

    addWidget(savesWidget, 0.1, 0.1, 0.8, 0.7);
}

void LoadGameMenu::setupUi()
{
    displaySaves();

    backButton = new QPushButton("Back", this);

    connect(backButton, &QPushButton::clicked, this, &LoadGameMenu::onLoadGameMenuClosed);

    addWidget(backButton, 0.4, 0.85, 0.2, 0.1);
}

LoadGameMenu::~LoadGameMenu()
{
    for (int i = 0; i < saveButtons.size(); i++)
    {
        delete saveButtons[i];
    }

    delete savesLayout;
    delete savesWidget;
    delete backButton;
}