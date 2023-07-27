#include <QResizeEvent>

#include "ScalableWidget.h"

ScalableWidget::ScalableWidget(QWidget* parent)
    : QWidget(parent)
{
    // Set the size of the widget initially
    resize(size());
}

void ScalableWidget::resizeEvent(QResizeEvent* event)
{
    int oldX = event->oldSize().width();
    int oldY = event->oldSize().height();

    int newX = event->size().width();
    int newY = event->size().height();

    if (oldX < 1 || oldY < 1)
    {
        return;
    }

    for (QWidget* widget : widgets)
    {
        int oldWidgetX = widget->x();
        int oldWidgetY = widget->y();

        double scaleRatioX = (double) newX / (double) oldX;
        double scaleRatioY = (double) newY / (double) oldY;

        int newWidgetX = std::round(oldWidgetX * scaleRatioX);
        int newWidgetY = std::round(oldWidgetY * scaleRatioY);

        int oldWidgetWidth = widget->width();
        int oldWidgetHeight = widget->height();

        int newWidgetWidth = std::round(oldWidgetWidth * scaleRatioX);
        int newWidgetHeight = std::round(oldWidgetHeight * scaleRatioY);

        widget->setGeometry(newWidgetX, newWidgetY, newWidgetWidth, newWidgetHeight);
    }
}

void ScalableWidget::addWidget(QWidget* widget, double percentX, double percentY, double percentWidth, double percentHeight)
{
    widgets.append(widget);

    if (percentX < 0 || percentY < 0 || percentWidth < 0 || percentHeight < 0)
    {
        return;
    }

    int windowWidth = size().width();
    int windowHeight = size().height();

    int widgetX = std::round(windowWidth * percentX);
    int widgetY = std::round(windowHeight * percentY);
    int widgetWidth = std::round(windowWidth * percentWidth);
    int widgetHeight = std::round(windowHeight * percentHeight);

    widget->setGeometry(widgetX, widgetY, widgetWidth, widgetHeight);
}

ScalableWidget::~ScalableWidget()
{
    // Pointers should be deleted by the parent widget
}