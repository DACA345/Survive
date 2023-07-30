#pragma once
#include <QWidget>

class ScalableWidget : public QWidget
{
    Q_OBJECT;

    public:
        ScalableWidget(QWidget* parent = nullptr);
        ~ScalableWidget();

    protected:
        void resizeEvent(QResizeEvent* event) override;
        void addWidget(QWidget* widget, double percentX = -1, double percentY = -1, double percentSizeX = -1, double percentSizeY = -1);

    private:
        QSize* oldSize = nullptr;

        QList<QWidget*> widgets;
};