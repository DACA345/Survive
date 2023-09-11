#pragma once

#include "../../scalablewidget.h"
#include "../../scalablelabel.h"
#include "../../svgpushbutton.h"

class SleepWidget : public ScalableWidget
{
    Q_OBJECT

    public:
        SleepWidget(QWidget *parent = nullptr);
        ~SleepWidget();

    signals:
        void close();

    private:
        void setupUi();

        ScalableLabel* sleepLabel;
        SVGPushButton* sleepButton;
};
