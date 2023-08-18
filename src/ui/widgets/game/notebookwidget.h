#pragma once

#include <QLabel>

#include "../scalablewidget.h"
#include "../svgpushbutton.h"
#include "../../../core/engine.h"

class NotebookWidget : public ScalableWidget
{
    Q_OBJECT

public:
    NotebookWidget(int day, QWidget* parent = nullptr);
    ~NotebookWidget();

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
