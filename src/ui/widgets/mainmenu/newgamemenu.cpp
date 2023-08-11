#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPainter>

#include "newgamemenu.h"
#include "../../../config/files.h"

LevelInfoWidget::LevelInfoWidget(const QString& levelJson, QWidget* parent)
    : ScalableWidget(parent)
{
    QFile levelFile(levelJson);
    levelFile.open(QIODevice::ReadOnly);

    QJsonDocument levelDoc = QJsonDocument::fromJson(levelFile.readAll());
    QJsonObject levelObj = levelDoc.object();

    id = levelObj["level_id"].toString();
    name = levelObj["title_name"].toString();

    QString pixmapPath = QString("mainmenu/levels/%1/level.png").arg(id);
    background = QPixmap(Files::textureFilePath(pixmapPath));

    setupUi();
}

void LevelInfoWidget::setupUi()
{
}

void LevelInfoWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), background);
}

void LevelInfoWidget::mousePressEvent(QMouseEvent* event)
{
    emit levelSelected(id);
}

LevelInfoWidget::~LevelInfoWidget()
{
}

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
            levelJsons.append(levelJsonPath);
        }
    }

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

    for (int i = 0; i < levelJsons.size(); i++)
    {
        LevelInfoWidget* levelButton = new LevelInfoWidget(levelJsons[i], this);
        levelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        levelButtons.append(levelButton);

        int row = i / columns;
        int col = i % columns;

        levelsLayout->addWidget(levelButton, row, col);

        connect(levelButton, &LevelInfoWidget::levelSelected ,this, [this](const QString& id)
            {
                emit levelSelected(id);
        });
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
    for (LevelInfoWidget* levelButton : levelButtons)
    {
        delete levelButton;
    }

    delete levelsLayout;
    delete levelsWidget;
    delete backButton;
}