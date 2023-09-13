#pragma once

#include <QMouseEvent>

#include "scalablewidget.h"

/**
 * @brief      This class describes a widget which can be dragged around.
 */
class DraggableWidget : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Create a new draggable widget instance.
         *
         * @param      parent  The parent
         */
        explicit DraggableWidget(QWidget* parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~DraggableWidget();

    protected:

        /**
         * @brief      Mouse press event handler.
         *
         * @param      event  The event
         */
        void mousePressEvent(QMouseEvent* event) override;

        /**
         * @brief      Mouse release event handler.
         *
         * @param      event  The event
         */
        void mouseReleaseEvent(QMouseEvent* event) override;

        /**
         * @brief      Mouse move event handler.
         *
         * @param      event  The event
         */
        void mouseMoveEvent(QMouseEvent* event) override;

    private:
        QPointF dragPosition;
};