#include <QPainter>

#include "notebookwidget.h"
#include "../../../../config/files.h"

#define IS_TOP_STACK(widget) (!widgetStack.isEmpty() && widgetStack.last().type == WidgetType::widget)
#define HIDE_STACK_WIDGET if (!hide) { widgetStack.removeLast(); }

NotebookWidget::NotebookWidget(const Engine& engine, QWidget* parent)
    : ScalableWidget(parent), engine(engine)
{
    loadStylesheet();
    loadGraphics();
    setupUi();
}

void NotebookWidget::displayPrevious()
{
    if (widgetStack.size() < 2)
    {
        return;
    }

    const WidgetInfo& info = widgetStack.at(widgetStack.size() - 2);
    switch (info.type)
    {
        case WidgetType::ACTION_MENU:
            displayActionMenu(false);
            break;
        case WidgetType::HISTORY_WIDGET:
            displayHistoryWidget(info.day, false);
            break;
        case WidgetType::RESULTS_WIDGET:
            displayResultsWidget(info.action, info.result, false);
            break;
        case WidgetType::SLEEP_WIDGET:
            displaySleepWidget(false);
            break;
    }
}

void NotebookWidget::closeCurrent(bool hide)
{
    if (widgetStack.isEmpty())
    {
        return;
    }

    switch (widgetStack.last().type)
    {
        case WidgetType::ACTION_MENU:
            closeActionMenu(hide);
            break;
        case WidgetType::HISTORY_WIDGET:
            closeHistoryWidget(hide);
            break;
        case WidgetType::RESULTS_WIDGET:
            closeResultsWidget(hide);
            break;
        case WidgetType::SLEEP_WIDGET:
            closeSleepWidget(hide);
            break;
    }
}

void NotebookWidget::displayActionMenu(bool hide)
{
    closeCurrent(hide);

    actionMenu = new ActionMenu(this);

    connect(actionMenu, &ActionMenu::findFood, this, &NotebookWidget::findFood);
    connect(actionMenu, &ActionMenu::findWater, this, &NotebookWidget::findWater);
    connect(actionMenu, &ActionMenu::explore, this, &NotebookWidget::explore);
    connect(actionMenu, &ActionMenu::rest, this, &NotebookWidget::rest);

    addWidget(actionMenu, 0, 0, 1, 1);

    actionMenu->show();

    raiseButtons();

    if (widgetStack.isEmpty() || widgetStack.last().type != WidgetType::ACTION_MENU)
    {
        widgetStack.append({ WidgetType::ACTION_MENU });
    }

}

void NotebookWidget::closeActionMenu(bool hide)
{
    if (!IS_TOP_STACK(ACTION_MENU))
    {
        return;
    }

    removeWidget(actionMenu);
    actionMenu->deleteLater();

    HIDE_STACK_WIDGET;
}

void NotebookWidget::displayHistoryWidget(int day, bool hide)
{
    titleLabel->hide();

    closeCurrent(hide);

    if (day <= 0)
    {
        day = engine.getDay().currentDay();
    }

    historyWidget = new HistoryWidget(engine.getJournal(), day, this);

    connect(historyWidget, &HistoryWidget::close, this, &NotebookWidget::displayPrevious);

    addWidget(historyWidget, 0, 0, 1, 1);

    historyWidget->show();

    raiseButtons();

    if (IS_TOP_STACK(HISTORY_WIDGET))
    {
        return;
    }
    else
    {
        widgetStack.append({ WidgetType::HISTORY_WIDGET, day });
    }
}

void NotebookWidget::closeHistoryWidget(bool hide)
{
    if (!IS_TOP_STACK(HISTORY_WIDGET))
    {
        return;
    }

    removeWidget(historyWidget);
    historyWidget->deleteLater();

    titleLabel->show();

    HIDE_STACK_WIDGET;
}

void NotebookWidget::displayResultsWidget(QString action, QString result, bool hide)
{
    closeCurrent(hide);

    resultWidget = new ResultWidget(action, result, this);

    connect(resultWidget, &ResultWidget::close, this, &NotebookWidget::displayPrevious);
    connect(resultWidget, &ResultWidget::close, this, &NotebookWidget::resultAcknowledged);

    addWidget(resultWidget, 0, 0, 1, 1);

    resultWidget->show();

    raiseButtons();

    const WidgetInfo& info = widgetStack.last();
    if (IS_TOP_STACK(RESULTS_WIDGET) && info.action == action && info.result == result)
    {
        return;
    }
    else
    {
        widgetStack.append({ WidgetType::RESULTS_WIDGET, -1, action, result });
    }

}

void NotebookWidget::closeResultsWidget(bool hide)
{
    if (!IS_TOP_STACK(RESULTS_WIDGET))
    {
        return;
    }

    removeWidget(resultWidget);
    resultWidget->deleteLater();

    HIDE_STACK_WIDGET;
}

void NotebookWidget::displaySleepWidget(bool hide)
{
    closeCurrent(hide);

    sleepWidget = new SleepWidget(this);
    
    connect(sleepWidget, &SleepWidget::close, this, &NotebookWidget::displayPrevious);
    connect(sleepWidget, &SleepWidget::close, this, &NotebookWidget::sleep);

    addWidget(sleepWidget, 0, 0, 1, 1);

    sleepWidget->show();

    raiseButtons();

    if (IS_TOP_STACK(SLEEP_WIDGET))
    {
        return;
    }
    else
    {
        widgetStack.append({ WidgetType::SLEEP_WIDGET });
    }

}

void NotebookWidget::closeSleepWidget(bool hide)
{
    if (!IS_TOP_STACK(SLEEP_WIDGET))
    {
        return;
    }

    removeWidget(sleepWidget);
    sleepWidget->deleteLater();

    HIDE_STACK_WIDGET(hide);
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

    historyButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/history.svg"), this);
    closeButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/return.svg"), this);

    connect(historyButton, &QPushButton::clicked, this, [this]()
        {
            displayHistoryWidget();
        }
    );

    connect(closeButton, &QPushButton::clicked, this, &NotebookWidget::hide);
    connect(closeButton, &QPushButton::clicked, this, &NotebookWidget::close);

    addWidget(titleLabel, 0, 0.1, 1, 0.075);

    addWidget(historyButton, 0.875, 0.1, 0.1, 0.065);
    addWidget(closeButton, 0.05, 0.1, 0.1, 0.065);

    displayActionMenu();
}

void NotebookWidget::raiseButtons()
{
    historyButton->raise();
    closeButton->raise();
}

NotebookWidget::~NotebookWidget()
{

}