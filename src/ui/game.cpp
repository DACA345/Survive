#include <QPainter>

#include "game.h"
#include "../config/files.h"

Game::Game(const QString& levelId, QWidget *parent)
    : ScalableWidget(parent), engine(levelId)
{
    loadGraphics();
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

void Game::loadGraphics()
{
    background = QPixmap(textureFile("set/image.png"));
}

void Game::setupUi()
{

}

Game::~Game()
{

}

