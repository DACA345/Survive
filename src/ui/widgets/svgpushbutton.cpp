#include <QPainter>

#include "svgpushbutton.h"

SVGPushButton::SVGPushButton(const QString& path, QWidget *parent)
    : QPushButton(parent)
{
    renderer = new QSvgRenderer(path, this);

    // Setup on hover effect, just changes opacity for svg
    opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(1.0);
    setGraphicsEffect(opacityEffect);

    animationGroup = new QParallelAnimationGroup(this);
    opacityAnimation = new QPropertyAnimation(opacityEffect, "opacity", this);

    opacityAnimation->setDuration(duration);
    opacityAnimation->setStartValue(startOpacity);
    opacityAnimation->setEndValue(endOpacity);

    animationGroup->addAnimation(opacityAnimation);

    // Set custom cursor for the button
    setCursor(Qt::PointingHandCursor);
}

void SVGPushButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setOpacity(opacityAnimation->currentValue().toDouble());

    renderer->render(&painter, rect());
}

void SVGPushButton::enterEvent(QEnterEvent* event)
{
    QPushButton::enterEvent(event);

    animationGroup->stop();

    opacityAnimation->setStartValue(opacityAnimation->currentValue().toDouble());
    opacityAnimation->setEndValue(endOpacity);

    animationGroup->start();
}

void SVGPushButton::leaveEvent(QEvent* event)
{
    QPushButton::leaveEvent(event);

    animationGroup->stop();

    opacityAnimation->setStartValue(opacityAnimation->currentValue().toDouble());
    opacityAnimation->setEndValue(startOpacity);

    animationGroup->start();
}

SVGPushButton::~SVGPushButton()
{

}
