#include <QPainter>

#include "gameover.h"
#include "../../../config/files.h"

GameOver::GameOver(QWidget *parent)
    : ScalableWidget(parent)
{
    loadGraphics();
    setupUi();
}

void GameOver::paintEvent(QPaintEvent* event)
{
    ScalableWidget::paintEvent(event);

    QPainter painter(this);
    painter.drawPixmap(rect(), background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void GameOver::loadGraphics()
{
    background = QPixmap(TEXTURE_FILE("gameover/background/image.png"));
}

void GameOver::setupUi()
{
    closeButton = new SVGPushButton(TEXTURE_FILE("mainmenu/icons/return.svg"), this);

    connect(closeButton, &SVGPushButton::clicked, this, &GameOver::close);

    addWidget(closeButton, 0.05, 0.025, 0.065, 0.09);
}

GameOver::~GameOver()
{
}
