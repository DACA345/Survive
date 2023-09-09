#include <QPainter>

#include "resultwidget.h"
#include "../../../../config/files.h"

ResultWidget::ResultWidget(QWidget *parent)
    : ScalableWidget(parent)
{
    setupUi();
}

void ResultWidget::setResult(const QString& action, const QString& result)
{
    actionLabel->setText(action);
    resultLabel->setText(result);
}

void ResultWidget::setupUi()
{
    actionLabel = new ScalableLabel(QString(), this);
    actionLabel->setAlignment(Qt::AlignCenter);

    resultLabel = new ScalableLabel(QString(), this);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setWordWrap(true);

    closeButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/okay.svg"), this);

    connect(closeButton, &QPushButton::clicked, this, &ResultWidget::close);

    addWidget(actionLabel, 0, 0.2, 1, 0.1);
    addWidget(resultLabel, 0.1, 0.425, 0.8, 0.25);

    addWidget(closeButton, 0.8, 0.875, 0.15, 0.045);
}

ResultWidget::~ResultWidget()
{
    delete actionLabel;
    delete resultLabel;
    delete closeButton;
}
