#include <QDirIterator>
#include <QPainter>

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

    loadGraphics();
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

void LoadGameMenu::paintEvent(QPaintEvent* event)
{
    ScalableWidget::paintEvent(event);

    QPainter painter(this);

    painter.drawPixmap(rect(), background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void LoadGameMenu::loadGraphics()
{
    background = QPixmap(TEXTURE_FILE("mainmenu/loadgame/background/image.png"));
}

void LoadGameMenu::setupUi()
{
    displaySaves();

    backButton = new SVGPushButton(TEXTURE_FILE("mainmenu/loadgame/text/back.svg"), this);

    connect(backButton, &QPushButton::clicked, this, &LoadGameMenu::onLoadGameMenuClosed);

    addWidget(backButton, 0.45, 0.875, 0.1, 0.075);
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