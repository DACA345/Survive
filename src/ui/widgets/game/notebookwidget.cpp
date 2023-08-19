#include <QPainter>

#include "notebookwidget.h"
#include "../../../config/files.h"

NotebookWidget::NotebookWidget(int day, QWidget* parent)
    : DraggableWidget(parent)
{
    this->day = day;

    loadStylesheet();
    loadGraphics();
    setupUi();
}

void NotebookWidget::paintEvent(QPaintEvent* event)
{
    ScalableWidget::paintEvent(event);

    QPainter painter(this);
    painter.drawPixmap(rect(), background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void NotebookWidget::loadStylesheet()
{
    QFile file(TEXTURE_FILE("ui/notebook/style/style.qss"));
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();
}

void NotebookWidget::loadGraphics()
{
    background = QPixmap(TEXTURE_FILE("ui/notebook/background/image.png"));
}

void NotebookWidget::setupUi()
{
    titleLabel = new QLabel(QString("Day %1").arg(day), this);
    titleLabel->setAlignment(Qt::AlignCenter);

    findFoodButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/food.svg"), this);
    findWaterButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/water.svg"), this);
    exploreButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/explore.svg"), this);
    restButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/rest.svg"), this);
    closeButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/return.svg"), this);

    connect(findFoodButton, &QPushButton::clicked, this, &NotebookWidget::findFood);
    connect(findWaterButton, &QPushButton::clicked, this, &NotebookWidget::findWater);
    connect(exploreButton, &QPushButton::clicked, this, &NotebookWidget::explore);
    connect(restButton, &QPushButton::clicked, this, &NotebookWidget::rest);
    connect(closeButton, &QPushButton::clicked, this, &NotebookWidget::hide);

    addWidget(titleLabel, 0, 0.05, 1, 0.2);

#define UI_NOTEBOOK_ACTION_X(width) ((1 - width) / 2)
#define UI_NOTEBOOK_ACTION_Y 0.25
#define UI_NOTEBOOK_ACTION_Y_GAP 0.15
#define UI_NOTEBOOK_ACTION_HEIGHT 0.06

    addWidget(findFoodButton, UI_NOTEBOOK_ACTION_X(0.35), UI_NOTEBOOK_ACTION_Y, 0.35, UI_NOTEBOOK_ACTION_HEIGHT);
    addWidget(findWaterButton, UI_NOTEBOOK_ACTION_X(0.42), UI_NOTEBOOK_ACTION_Y + UI_NOTEBOOK_ACTION_Y_GAP, 0.42, UI_NOTEBOOK_ACTION_HEIGHT);
    addWidget(exploreButton, UI_NOTEBOOK_ACTION_X(0.325), UI_NOTEBOOK_ACTION_Y + UI_NOTEBOOK_ACTION_Y_GAP * 2, 0.325, UI_NOTEBOOK_ACTION_HEIGHT);
    addWidget(restButton, UI_NOTEBOOK_ACTION_X(0.185), UI_NOTEBOOK_ACTION_Y + UI_NOTEBOOK_ACTION_Y_GAP * 3, 0.185, UI_NOTEBOOK_ACTION_HEIGHT);

    addWidget(closeButton, 0.05, 0.1, 0.1, 0.065);
}

NotebookWidget::~NotebookWidget()
{
    delete titleLabel;

    delete findFoodButton;
    delete findWaterButton;
    delete exploreButton;
    delete restButton;
    delete closeButton;
}