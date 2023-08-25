#include <QResizeEvent>

#include "scalablewidget.h"

ScalableWidget::ScalableWidget(QWidget* parent)
    : QWidget(parent)
{

}

void ScalableWidget::resizeEvent(QResizeEvent* event)
{
    if (event->oldSize() == event->size())
    {
        return;
    }

    redraw();
}

void ScalableWidget::redraw()
{
    for (auto widget : widgets.keys())
    {
        setScaledGeometry(widget);
    }
}

void ScalableWidget::addWidget(QWidget* widget, double percentX, double percentY, double percentWidth, double percentHeight)
{
    if (percentX < 0 || percentY < 0 || percentWidth < 0 || percentHeight < 0)
    {
        throw new std::invalid_argument("ScalableWidget::addWidget Percentages cannot be negative");
    }

    widgets[widget] = { percentX, percentY, percentWidth, percentHeight };

    setScaledGeometry(widget);
}

void ScalableWidget::removeWidget(QWidget* widget)
{
    widgets.remove(widget);
}

void ScalableWidget::setScaledGeometry(QWidget* widget)
{
    ChildInfo info = widgets[widget];

    int windowWidth = size().width();
    int windowHeight = size().height();

    int widgetX = std::round(windowWidth * info.percentX);
    int widgetY = std::round(windowHeight * info.percentY);
    int widgetWidth = std::round(windowWidth * info.percentWidth);
    int widgetHeight = std::round(windowHeight * info.percentHeight);

    widget->setGeometry(widgetX, widgetY, widgetWidth, widgetHeight);
}

ScalableWidget::~ScalableWidget()
{
    // Pointers should be deleted by the parent widget
}