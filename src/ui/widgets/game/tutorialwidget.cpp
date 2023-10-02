#include <QPainter>

#include "tutorialwidget.h"

#include "../../../config/files.h"

TutorialWidget::TutorialWidget(QWidget* parent)
    : ScalableWidget(parent)
{

    loadGraphics();
    setupUi();
}

void TutorialWidget::paintEvent(QPaintEvent* event)
{
    ScalableWidget::paintEvent(event);
    QPainter painter(this);

    painter.drawPixmap(rect(), overlay.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void TutorialWidget::loadGraphics()
{
    overlay = QPixmap(TEXTURE_FILE("ui/help/background/overlay.svg"));
}

void TutorialWidget::setupUi()
{
    bannerWidget = new QSvgWidget(TEXTURE_FILE("ui/help/background/banner.svg"), this);

    bodyLabel = new ScalableLabel(TUTORIAL_BODY, this, true);
    bodyLabel->setWordWrap(true);
    bodyLabel->setStyleSheet("QLabel { color: white; }");

    closeButton = new SVGPushButton(TEXTURE_FILE("mainmenu/icons/return.svg"), this);

    connect(closeButton, &QPushButton::clicked, this, &TutorialWidget::close);

    addWidget(bannerWidget, 0.2, 0.1, 0.6, 0.8);
    addWidget(bodyLabel, 0.25, 0.25, 0.5, 0.6);

    addWidget(closeButton, 0.05, 0.025, 0.065, 0.09);
}

TutorialWidget::~TutorialWidget()
{
}

