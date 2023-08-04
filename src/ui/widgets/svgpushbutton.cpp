#include <QPainter>
#include <QGraphicsOpacityEffect>

#include "svgpushbutton.h"

SVGPushButton::SVGPushButton(const QString& path, QWidget *parent)
    : QPushButton(parent)
{
    renderer = new QSvgRenderer(path, this);
}

void SVGPushButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    renderer->render(&painter, rect());
}

SVGPushButton::~SVGPushButton()
{
    delete renderer;
}
