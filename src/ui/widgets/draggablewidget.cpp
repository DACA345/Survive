#include <QWindow>

#include "draggablewidget.h"

DraggableWidget::DraggableWidget(QWidget* parent)
    : ScalableWidget(parent)
{
    setCursor(Qt::OpenHandCursor);
}

void DraggableWidget::mousePressEvent(QMouseEvent* event)
{
    setCursor(Qt::ClosedHandCursor);

    dragPosition = event->globalPos() - frameGeometry().topLeft();
}

void DraggableWidget::mouseReleaseEvent(QMouseEvent* event)
{
    setCursor(Qt::OpenHandCursor);
}

void DraggableWidget::mouseMoveEvent(QMouseEvent* event)
{
    // Prevent moving outside of the window
    QPointF globalPos = event->globalPosition();
    QPointF windowPos = window()->frameGeometry().topLeft();
    QSize windowSize = window()->frameGeometry().size();
    QPointF windowBottomRight = windowPos + QPointF(windowSize.width(), windowSize.height());
    if (globalPos.x() < windowPos.x() || globalPos.y() < windowPos.y() || globalPos.x() > windowBottomRight.x() || globalPos.y() > windowBottomRight.y())
    {
        return;
    }

    move((globalPos - dragPosition).toPoint());
    redraw();
}

DraggableWidget::~DraggableWidget()
{
}