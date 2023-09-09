#include <QPainter>

#include "notebookwidget.h"
#include "../../../../config/files.h"

NotebookWidget::NotebookWidget(const Engine& engine, QWidget* parent)
    : ScalableWidget(parent), engine(engine)
{
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

void NotebookWidget::displayHistoryWidget()
{
    historyButton->hide();
    titleLabel->hide();

    closeActionMenu();

    historyWidget->showDay(engine.getDay().currentDay());
    historyWidget->show();
}

void NotebookWidget::closeHistoryWidget()
{
    historyWidget->hide();

    titleLabel->show();
    historyButton->show();

    displayActionMenu();
}

void NotebookWidget::displayResultsWidget(QString action, QString result)
{
    historyButton->hide();

    closeActionMenu();

    resultWidget->setResult(action, result);
    resultWidget->show();
}

void NotebookWidget::closeResultsWidget()
{
    resultWidget->hide();
    emit resultAcknowledged();

    displayActionMenu();

    historyButton->show();
}

void NotebookWidget::updateDay()
{
    titleLabel->setText(QString("Day %1").arg(engine.getDay().currentDay()));
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
    titleLabel = new ScalableLabel(QString("Day %1").arg(engine.getDay().currentDay()), this);
    titleLabel->setAlignment(Qt::AlignCenter);

    actionMenu = new ActionMenu(this);

    historyWidget = new HistoryWidget(engine.getJournal(), engine.getDay().currentDay(), this);
    historyWidget->hide();

    resultWidget = new ResultWidget(this);
    resultWidget->hide();

    historyButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/history.svg"), this);
    closeButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/return.svg"), this);

    connect(actionMenu, &ActionMenu::findFood, this, &NotebookWidget::findFood);
    connect(actionMenu, &ActionMenu::findWater, this, &NotebookWidget::findWater);
    connect(actionMenu, &ActionMenu::explore, this, &NotebookWidget::explore);
    connect(actionMenu, &ActionMenu::rest, this, &NotebookWidget::rest);

    connect(historyWidget, &HistoryWidget::close, this, &NotebookWidget::closeHistoryWidget);

    connect(resultWidget, &ResultWidget::close, this, &NotebookWidget::closeResultsWidget);

    connect(historyButton, &QPushButton::clicked, this, &NotebookWidget::displayHistoryWidget);

    connect(closeButton, &QPushButton::clicked, this, &NotebookWidget::hide);
    connect(closeButton, &QPushButton::clicked, this, &NotebookWidget::close);

    addWidget(titleLabel, 0, 0.1, 1, 0.075);

    addWidget(actionMenu, 0, 0, 1, 1);
    addWidget(historyWidget, 0, 0, 1, 1);
    addWidget(resultWidget, 0, 0, 1, 1);

    addWidget(historyButton, 0.875, 0.1, 0.1, 0.065);
    addWidget(closeButton, 0.05, 0.1, 0.1, 0.065);
}

NotebookWidget::~NotebookWidget()
{
    delete actionMenu;
    delete resultWidget;

    delete titleLabel;
    delete closeButton;
}