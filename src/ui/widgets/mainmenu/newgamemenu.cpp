#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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

    setupUi();
    loadGraphics();

    setCursor(Qt::PointingHandCursor);
}

void LevelInfoWidget::setupUi()
{
}

void LevelInfoWidget::loadGraphics()
{
    QDir textureDir(TEXTURE_FILE(QString("mainmenu/levels/%1").arg(id)));
    QFile manifestJson = QFile(textureDir.filePath("manifest.json"));
    manifestJson.open(QIODevice::ReadOnly);

    QJsonDocument manifest = QJsonDocument::fromJson(manifestJson.readAll());
    QJsonObject manifestObj = manifest.object();

    QString backgroundFile = manifestObj["background"].toString();

    QJsonObject labelObj = manifestObj["label"].toObject();
    QString labelFile = labelObj["file"].toString();
    QJsonArray offsetArray = labelObj["offset"].toArray();
    QJsonArray sizeArray = labelObj["size"].toArray();

    labelRenderer = new QSvgRenderer(textureDir.filePath(labelFile));
    labelRect = QRectF(
        offsetArray[0].toDouble() / 100,
        offsetArray[1].toDouble() / 100,
        sizeArray[0].toDouble() / 100,
        sizeArray[1].toDouble() / 100
    );


    QJsonObject filtersObj = manifestObj["filters"].toObject();
    QDir filtersDir(textureDir.filePath("filters"));

    QJsonArray filterArray = filtersObj["normal"].toArray();
    QJsonArray hoverArray = filtersObj["hover"].toArray();

    for (const QJsonValue& filter : filterArray)
    {
        QString filterFile = filter.toString();

        defaultFilters.append(new QSvgRenderer(filtersDir.filePath(filterFile)));
    }

    for (const QJsonValue& filter : hoverArray)
    {
        QString filterFile = filter.toString();

        hoverFilters.append(new QSvgRenderer(filtersDir.filePath(filterFile)));
    }

    background = QPixmap(textureDir.filePath(backgroundFile));

}

void LevelInfoWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), background);

    QList<QSvgRenderer*>& filters = isHovered ? hoverFilters : defaultFilters;

    for (QSvgRenderer* filter : filters)
    {
        filter->render(&painter, rect());
    }

    QRectF proportionRect = QRectF(
        labelRect.left() * width(),
        labelRect.top() * height(),
        labelRect.width() * width(),
        labelRect.height() * height()
    );

    labelRenderer->render(&painter, proportionRect);
}

void LevelInfoWidget::mousePressEvent(QMouseEvent* event)
{
    emit levelSelected(id);
}

void LevelInfoWidget::enterEvent(QEnterEvent* event)
{
    isHovered = true;
    QWidget::enterEvent(event);

    repaint();
}

void LevelInfoWidget::leaveEvent(QEvent* event)
{
    isHovered = false;
    QWidget::leaveEvent(event);

    repaint();
}

LevelInfoWidget::~LevelInfoWidget()
{
    for (QSvgRenderer* filter : defaultFilters)
    {
        delete filter;
    }

    for (QSvgRenderer* filter : hoverFilters)
    {
        delete filter;
    }

    delete labelRenderer;
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