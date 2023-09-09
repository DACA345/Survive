#include <QPainter>

#include "notebookwidget.h"
#include "../../../../config/files.h"

NotebookWidget::NotebookWidget(int day, QWidget* parent)
    : ScalableWidget(parent)
{
    this->day = day;

    loadStylesheet();
    loadGraphics();
    setupUi();

    displayActionMenu();
}

void NotebookWidget::displayActionMenu()
{
    actionMenu->show();
}

void NotebookWidget::closeActionMenu()
{
    actionMenu->hide();
}

void NotebookWidget::displayResultsWidget(QString action, QString result)
{
    closeActionMenu();

    resultWidget->setResult(action, result);

    resultWidget->show();
}

void NotebookWidget::closeResultsWidget()
{
    resultWidget->hide();
    emit resultAcknowledged();
    displayActionMenu();
}

void NotebookWidget::updateDay(int day)
{
    this->day = day;
    titleLabel->setText(QString("Day %1").arg(day));
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
    titleLabel = new ScalableLabel(QString("Day %1").arg(day), this);
    titleLabel->setAlignment(Qt::AlignCenter);

    actionMenu = new ActionMenu(this);
    resultWidget = new ResultWidget(this);
    resultWidget->hide();

    closeButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/return.svg"), this);

    connect(actionMenu, &ActionMenu::findFood, this, &NotebookWidget::findFood);
    connect(actionMenu, &ActionMenu::findWater, this, &NotebookWidget::findWater);
    connect(actionMenu, &ActionMenu::explore, this, &NotebookWidget::explore);
    connect(actionMenu, &ActionMenu::rest, this, &NotebookWidget::rest);

    connect(resultWidget, &ResultWidget::close, this, &NotebookWidget::closeResultsWidget);

    connect(closeButton, &QPushButton::clicked, this, &NotebookWidget::hide);
    connect(closeButton, &QPushButton::clicked, this, &NotebookWidget::close);

    addWidget(titleLabel, 0, 0.1, 1, 0.075);

    addWidget(actionMenu, 0, 0, 1, 1);
    addWidget(resultWidget, 0, 0, 1, 1);

    addWidget(closeButton, 0.05, 0.1, 0.1, 0.065);
}

NotebookWidget::~NotebookWidget()
{
    delete actionMenu;
    delete resultWidget;

    delete titleLabel;
    delete closeButton;
}