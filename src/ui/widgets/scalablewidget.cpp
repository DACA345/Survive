#include <QResizeEvent>

#include "scalablewidget.h"

ScalableWidget::ScalableWidget(QWidget* parent)
    : QWidget(parent)
{
    // Set the size of the widget initially
    resize(size());
}

// NOTE(Callum): Does not work perfectly, likely due to rounding errors
// Widgets can get skewed and misplaced
// Not a priority fix, can prevent draggable resizing
void ScalableWidget::resizeEvent(QResizeEvent* event)
{
    QSize useSize = event->oldSize();

    // Cannot scale as the old size is invalid
    if (!event->oldSize().isValid())
    {
        if (oldSize != nullptr)
        {
            useSize = *oldSize;
        }
        else
        {
            oldSize = new QSize(event->size());
            return;
        }
    }

    int oldX = useSize.width();
    int oldY = useSize.height();

    int newX = event->size().width();
    int newY = event->size().height();

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

    oldSize = new QSize(size());
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
    delete oldSize;

    // Pointers should be deleted by the parent widget
}