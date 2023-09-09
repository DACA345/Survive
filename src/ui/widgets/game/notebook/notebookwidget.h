#pragma once

#include <QLabel>

#include "actionmenu.h"
#include "resultwidget.h"
#include "../../scalablelabel.h"
#include "../../scalablewidget.h"
#include "../../svgpushbutton.h"

class NotebookWidget : public ScalableWidget
{
    Q_OBJECT

    public:
        explicit NotebookWidget(int day, QWidget* parent = nullptr);
        ~NotebookWidget();

        void displayActionMenu();
        void displayResultsWidget(QString action, QString result);

        void updateDay(int day);

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
        void closeResultsWidget();

        int day;

        // Ui elements
        ActionMenu* actionMenu;
        ResultWidget* resultWidget;

        ScalableLabel *titleLabel;

        SVGPushButton* closeButton;

        QPixmap background;
};
