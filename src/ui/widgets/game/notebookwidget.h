#pragma once

#include <QLabel>

#include "../draggablewidget.h"
#include "../scalablewidget.h"
#include "../svgpushbutton.h"
#include "../../../core/engine.h"

class NotebookWidget : public DraggableWidget
{
    Q_OBJECT

    public:
        explicit NotebookWidget(int day, QWidget* parent = nullptr);
        ~NotebookWidget();

    signals:
        void findFood();
        void findWater();
        void explore();
        void rest();
        void close();

    private:
        void paintEvent(QPaintEvent* event) override;

        void loadStylesheet();
        void loadGraphics();
        void setupUi();

        int day;

        // Ui elements
        QLabel* titleLabel;

        SVGPushButton* findFoodButton;
        SVGPushButton* findWaterButton;
        SVGPushButton* exploreButton;
        SVGPushButton* restButton;
        SVGPushButton* closeButton;

        QPixmap background;
};
