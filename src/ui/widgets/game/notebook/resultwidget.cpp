#include <QPainter>

#include "resultwidget.h"
#include "../../../../config/files.h"

ResultWidget::ResultWidget(const QString& action, const QString& result, QWidget *parent)
    : ScalableWidget(parent), action(action), result(result)
{
    setupUi();
}

void ResultWidget::setResult(const QString& action, const QString& result)
{
    this->action = action;
    this->result = result;
    actionLabel->setText(action);
    resultLabel->setText(result);
}

void ResultWidget::setupUi()
{
    actionLabel = new ScalableLabel(action, this);
    actionLabel->setAlignment(Qt::AlignCenter);

    resultLabel = new QLabel(result, this);
    resultLabel->setFont(QFont("Comic Sans MS", 36));
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setWordWrap(true);

    closeButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/okay.svg"), this);

    connect(closeButton, &QPushButton::clicked, this, &ResultWidget::close);

    addWidget(actionLabel, 0, 0.2, 1, 0.1);
    addWidget(resultLabel, 0.1, 0.125, 0.8, 0.75);

    addWidget(closeButton, 0.8, 0.875, 0.15, 0.045);
}

ResultWidget::~ResultWidget()
{

}
