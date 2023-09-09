#pragma once

#include <QLabel>

#include "actionmenu.h"
#include "historywidget.h"
#include "resultwidget.h"
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
        void displayHistoryWidget();
        void displayResultsWidget(QString action, QString result);

        void updateDay();

    signals:
        void findFood();
        void findWater();
        void explore();
        void rest();

        void resultAcknowledged();

        void close();

    private:
        void paintEvent(QPaintEvent* event) override;

        void loadStylesheet();
        void loadGraphics();
        void setupUi();

        void closeActionMenu();
        void closeHistoryWidget();
        void closeResultsWidget();

        const Engine& engine;

        // Ui elements
        ActionMenu* actionMenu;
        HistoryWidget* historyWidget;
        ResultWidget* resultWidget;

        ScalableLabel *titleLabel;

        SVGPushButton* historyButton;
        SVGPushButton* closeButton;

        QPixmap background;
};
