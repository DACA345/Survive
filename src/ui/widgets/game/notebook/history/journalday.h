#pragma once

#include "../../../scalablelabel.h"
#include "../../../scalablewidget.h"
#include "../../../../../core/journal.h"

class JournalDay : public ScalableWidget
{
    Q_OBJECT

    public:
        JournalDay(const DayEntry& day, QWidget *parent = nullptr);
        ~JournalDay();

    private:
        void setupUi(const DayEntry& day);

        // Ui elements
        ScalableLabel* dayEventLabel;
        QList<ScalableLabel*> dayActions;
        QList<ScalableLabel*> dayResults;
};
