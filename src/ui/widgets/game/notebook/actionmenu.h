#pragma once

#include "../../scalablewidget.h"
#include "../../svgpushbutton.h"

class ActionMenu : public ScalableWidget
{
    Q_OBJECT

    public:
        ActionMenu(QWidget *parent = nullptr);
        ~ActionMenu();

    signals:
        void findFood();
        void findWater();
        void explore();
        void rest();

    private:
        void setupUi();

        SVGPushButton* findFoodButton;
        SVGPushButton* findWaterButton;
        SVGPushButton* exploreButton;
        SVGPushButton* restButton;
};
