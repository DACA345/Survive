#include "game.h"
#include <QPainter>

#include "game.h"
#include "../config/files.h"

Game::Game(const QString& levelId, QWidget *parent)
    : ScalableWidget(parent), engine(levelId)
{
    loadGraphics();
    setupUi();
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
    energyLabel = new QLabel(QString("Energy: %1").arg(engine.getEnergy()), this);
    hungerLabel = new QLabel(QString("Hunger: %1").arg(engine.getHunger()), this);
    thirstLabel = new QLabel(QString("Thirst: %1").arg(engine.getThirst()), this);
    healthLabel = new QLabel(QString("Health: %1").arg(engine.getHealth()), this);

    findFoodButton = new QPushButton("Find Food", this);
    findWaterButton = new QPushButton("Find Water", this);
    exploreButton = new QPushButton("Explore", this);
    restButton = new QPushButton("Rest", this);

    connect(findFoodButton, &QPushButton::clicked, this, &Game::onFindFood);
    connect(findWaterButton, &QPushButton::clicked, this, &Game::onFindWater);
    connect(exploreButton, &QPushButton::clicked, this, &Game::onExplore);
    connect(restButton, &QPushButton::clicked, this, &Game::onRest);

    addWidget(energyLabel, 0.9, 0.1, 0.1, 0.1);
    addWidget(hungerLabel, 0.9, 0.3, 0.1, 0.1);
    addWidget(thirstLabel, 0.9, 0.5, 0.1, 0.1);
    addWidget(healthLabel, 0.9, 0.7, 0.1, 0.1);

    addWidget(findFoodButton, 0.1, 0.1, 0.2, 0.2);
    addWidget(findWaterButton, 0.1, 0.3, 0.2, 0.2);
    addWidget(exploreButton, 0.1, 0.5, 0.2, 0.2);
    addWidget(restButton, 0.1, 0.7, 0.2, 0.2);
}

void Game::updateUi()
{
    energyLabel->setText(QString("Energy: %1").arg(engine.getEnergy()));
    hungerLabel->setText(QString("Hunger: %1").arg(engine.getHunger()));
    thirstLabel->setText(QString("Thirst: %1").arg(engine.getThirst()));
    healthLabel->setText(QString("Health: %1").arg(engine.getHealth()));
}

Game::~Game()
{
    delete findFoodButton;
    delete findWaterButton;
    delete exploreButton;
    delete restButton;
}

