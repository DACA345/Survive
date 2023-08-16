#include "game.h"
#include <QPainter>

#include "game.h"
#include "../config/files.h"

Game::Game(const QString& levelId, QWidget *parent)
    : ScalableWidget(parent), engine(levelId)
{
    loadGraphics();
    setupUi();
    updateUi();
}

void Game::paintEvent(QPaintEvent* event)
{
    ScalableWidget::paintEvent(event);

    QPainter painter(this);

    painter.drawPixmap(rect(), background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

QString Game::textureFile(const QString& name)
{
    return TEXTURE_FILE(QString("levels/%1/%2").arg(engine.getLevel().getInfo().id).arg(name));
}

void Game::onFindFood()
{
    engine.findFood();
    updateUi();
}

void Game::onFindWater()
{
    engine.findWater();
    updateUi();
}

void Game::onExplore()
{
    engine.explore();
    updateUi();
}

void Game::onRest()
{
    engine.rest();
    updateUi();
}

void Game::loadGraphics()
{
    background = QPixmap(textureFile("set/image.png"));
}

void Game::setupUi()
{
    bars = new QSvgWidget(TEXTURE_FILE("ui/bars/bars.svg"), this);
    healthBarFill = new QSvgWidget(TEXTURE_FILE("ui/bars/fill/health.svg"), this);
    thirstBarFill = new QSvgWidget(TEXTURE_FILE("ui/bars/fill/thirst.svg"), this);
    hungerBarFill = new QSvgWidget(TEXTURE_FILE("ui/bars/fill/hunger.svg"), this);
    energyBarFill = new QSvgWidget(TEXTURE_FILE("ui/bars/fill/wellness.svg"), this);

    findFoodButton = new QPushButton("Find Food", this);
    findWaterButton = new QPushButton("Find Water", this);
    exploreButton = new QPushButton("Explore", this);
    restButton = new QPushButton("Rest", this);

    connect(findFoodButton, &QPushButton::clicked, this, &Game::onFindFood);
    connect(findWaterButton, &QPushButton::clicked, this, &Game::onFindWater);
    connect(exploreButton, &QPushButton::clicked, this, &Game::onExplore);
    connect(restButton, &QPushButton::clicked, this, &Game::onRest);

    addWidget(bars, 1 - 0.295, 0.01, 0.285, 0.2);

    addWidget(findFoodButton, 0.1, 0.1, 0.2, 0.2);
    addWidget(findWaterButton, 0.1, 0.3, 0.2, 0.2);
    addWidget(exploreButton, 0.1, 0.5, 0.2, 0.2);
    addWidget(restButton, 0.1, 0.7, 0.2, 0.2);
}

void Game::updateUi()
{
    // Bar updates
    const double yGap = 0.015;
    const double heightPercentage = 0.0385;

    addWidget(healthBarFill, 0.7325, 0.011, 0.2575 * ((double) engine.getHealth() / (double) BAR_MAX), heightPercentage);
    addWidget(thirstBarFill, 0.7325, 0.011 + yGap + heightPercentage, 0.2575 * ((double) engine.getThirst() / (double) BAR_MAX), heightPercentage);
    addWidget(hungerBarFill, 0.7325, 0.011 + 2 * yGap + 2 * heightPercentage, 0.2575 * ((double) engine.getHunger() / (double) BAR_MAX), heightPercentage);
    addWidget(energyBarFill, 0.7325, 0.011 + 3 * yGap + 3 * heightPercentage, 0.2575 * ((double) engine.getEnergy() / (double) BAR_MAX), heightPercentage);
}

Game::~Game()
{
    delete findFoodButton;
    delete findWaterButton;
    delete exploreButton;
    delete restButton;
}

