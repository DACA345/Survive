#include "sleepwidget.h"
#include "../../../../config/files.h"

#define SLEEP_TEXT "You return to your camp exhausted for the day."

SleepWidget::SleepWidget(QWidget *parent)
    : ScalableWidget(parent)
{
    setupUi();
}

void SleepWidget::setupUi()
{
    sleepLabel = new ScalableLabel(SLEEP_TEXT, this);
    sleepLabel->setAlignment(Qt::AlignCenter);

    sleepButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/okay.svg"), this);

    connect(sleepButton, &QPushButton::clicked, this, &SleepWidget::close);

    addWidget(sleepLabel, 0.1, 0.125, 0.8, 0.75);
    addWidget(sleepButton, 0.8, 0.875, 0.15, 0.045);
}

SleepWidget::~SleepWidget()
{
}
