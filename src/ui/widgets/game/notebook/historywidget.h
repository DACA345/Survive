#pragma once

#include "history/journalday.h"
#include "../../scalablelabel.h"
#include "../../scalablewidget.h"
#include "../../svgpushbutton.h"
#include "../../../../core/journal.h"

class HistoryWidget : public ScalableWidget
{
    Q_OBJECT

    public:
        HistoryWidget(const Journal& journal, int currentDay = 1, QWidget *parent = nullptr);
        ~HistoryWidget();

        void showDay(int day);

    signals:
        void close();

    private:
        void setupUi();

        const Journal& journal;

        int currentDay;

        // Ui elements

        JournalDay* journalDay;

        ScalableLabel* titleLabel;
        ScalableLabel* dayLabel;

        SVGPushButton* prevButton;
        SVGPushButton* nextButton;

        SVGPushButton* closeButton;
};
