#pragma once

#include "../../../scalablelabel.h"
#include "../../../scalablewidget.h"
#include "../../../../../core/journal.h"

/**
 * @brief      This class describes a journal day within the history widget.
 */
class JournalDay : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Constructs a new instance.
         *
         * @param[in]  day     The day
         * @param      parent  The parent
         */
        explicit JournalDay(const DayEntry& day, QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~JournalDay();

    private:
        /**
         * @brief      Sets up the UI for a given day.
         *
         * @param[in]  day   The day
         */
        void setupUi(const DayEntry& day);

        // Ui elements
        ScalableLabel* dayEventLabel;
        QList<ScalableLabel*> dayActions;
        QList<ScalableLabel*> dayResults;
};
