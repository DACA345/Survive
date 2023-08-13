#pragma once
#include <QWidget>

/**
 * @brief      This class describes a widget which scales it's children with the widget size.
 */
class ScalableWidget : public QWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Create a new scalable widget instance.
         *
         * @param      parent  The parent
         */
        ScalableWidget(QWidget* parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~ScalableWidget();

    protected:
        /**
         * @brief      Resize event handler.
         *
         * @param      event  The event
         */
        void resizeEvent(QResizeEvent* event) override;

        /**
         * @brief      Adds a widget which will be scaled.
         *
         * @param      widget        The widget
         * @param[in]  percentX      The percent x
         * @param[in]  percentY      The percent y
         * @param[in]  percentSizeX  The percent size x
         * @param[in]  percentSizeY  The percent size y
         */
        void addWidget(QWidget* widget, double percentX, double percentY, double percentSizeX, double percentSizeY);

        /**
         * @brief      Removes a widget.
         *
         * @param      widget  The widget
         */
        void removeWidget(QWidget* widget);

    private:
        /**
         * @brief      Information for a child widget.
         */
        struct ChildInfo
        {
            double percentX;
            double percentY;
            double percentWidth;
            double percentHeight;
        };

        /**
         * @brief      Sets the scaled geometry. See QWidget setGeometry.
         *
         * @param      widget  The widget
         */
        void setScaledGeometry(QWidget* widget);

        QMap<QWidget*, ChildInfo> widgets;
};