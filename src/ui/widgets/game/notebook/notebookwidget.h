#pragma once

#include <QLabel>

#include "actionmenu.h"
#include "historywidget.h"
#include "resultwidget.h"
#include "sleepwidget.h"
#include "../../scalablelabel.h"
#include "../../scalablewidget.h"
#include "../../svgpushbutton.h"

class NotebookWidget : public ScalableWidget
{
    Q_OBJECT

    public:
        explicit NotebookWidget(const Engine& engine, QWidget* parent = nullptr);
        ~NotebookWidget();

        void displayActionMenu();
        void displayHistoryWidget(int day = -1);
        void displayResultsWidget(QString action, QString result);
        void displaySleepWidget();

        void updateDay();

    signals:
        void findFood();
        void findWater();
        void explore();
        void rest();
        void sleep();

        void resultAcknowledged();

        void close();

    private:
        enum class WidgetType
        {
            ACTION_MENU,
            HISTORY_WIDGET,
            RESULTS_WIDGET,
            SLEEP_WIDGET
        };

        struct WidgetInfo
        {
            WidgetType type;

            // History
            int day;

            // Result
            QString action;
            QString result;
        };

        void paintEvent(QPaintEvent* event) override;

        void loadStylesheet();
        void loadGraphics();
        void setupUi();
        void raiseButtons();

        void displayPrevious();

        void closeCurrent(bool hide = false);

        void closeActionMenu(bool hide = false);
        void closeHistoryWidget(bool hide = false);
        void closeResultsWidget(bool hide = false);
        void closeSleepWidget(bool hide = false);

        const Engine& engine;

        QList<WidgetInfo> widgetStack;

        // Ui elements
        ActionMenu* actionMenu = nullptr;
        HistoryWidget* historyWidget;
        ResultWidget* resultWidget;
        SleepWidget* sleepWidget;

        ScalableLabel *titleLabel;

        SVGPushButton* historyButton;
        SVGPushButton* closeButton;

        QPixmap background;
};
