#pragma once
#include <QWidget>

class ScalableWidget : public QWidget
{
    Q_OBJECT

    public:
        ScalableWidget(QWidget* parent = nullptr);
        ~ScalableWidget();

    protected:
        void resizeEvent(QResizeEvent* event) override;
        void addWidget(QWidget* widget, double percentX, double percentY, double percentSizeX, double percentSizeY);
        void removeWidget(QWidget* widget);

    private:
        struct ChildInfo
        {
            double percentX;
            double percentY;
            double percentWidth;
            double percentHeight;
        };

        void setScaledGeometry(QWidget* widget);

        QMap<QWidget*, ChildInfo> widgets;
};