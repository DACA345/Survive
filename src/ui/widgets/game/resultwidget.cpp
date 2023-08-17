#include <QPainter>

#include "resultwidget.h"
#include "../../../config/files.h"

ResultWidget::ResultWidget(QWidget *parent)
    : ScalableWidget(parent)
{
    loadGraphics();
    setupUi();
}

void ResultWidget::paintEvent(QPaintEvent* event)
{
    ScalableWidget::paintEvent(event);

    QPainter painter(this);
    painter.drawPixmap(rect(), background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ResultWidget::showResult(ActionResult result)
{
    resultLabel->setText(result.message);

    if (isHidden())
        show();
}

void ResultWidget::loadGraphics()
{
    background = QPixmap(TEXTURE_FILE("ui/result/background/image.png"));
}

void ResultWidget::setupUi()
{
    resultLabel = new QLabel(this);
    resultLabel->setAlignment(Qt::AlignCenter);

    closeButton = new QPushButton("Ok", this);

    connect(closeButton, &QPushButton::clicked, this, &ResultWidget::hide);

    addWidget(resultLabel, 0, 0, 1, 0.2);

    addWidget(closeButton, 0.45, 0.85, 0.1, 0.1);
}

ResultWidget::~ResultWidget()
{
    delete resultLabel;
    delete closeButton;
}
