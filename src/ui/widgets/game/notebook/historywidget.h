#pragma once

#include "history/journalday.h"
#include "../../scalablelabel.h"
#include "../../scalablewidget.h"
#include "../../svgpushbutton.h"
#include "../../../../core/journal.h"

/**
 * @brief      This class describes the history widget representing the journal in the notebook.
 */
class HistoryWidget : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Constructs a new instance.
         *
         * @param[in]  journal     The journal
         * @param[in]  currentDay  The current day
         * @param      parent      The parent
         */
        explicit HistoryWidget(const Journal& journal, int currentDay = 1, QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~HistoryWidget();

        /**
         * @brief      Shows the journal entry for a day.
         *
         * @param[in]  day   The day
         */
        void showDay(int day);

    signals:
        /**
         * @brief      Called when the user has requested to close the widget.
         */
        void close();

    private:
        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        /**
         * The representative journal.
         */
        const Journal& journal;

        int currentDay;

        // Ui elements

        JournalDay* journalDay = nullptr;

        ScalableLabel* titleLabel;
        ScalableLabel* dayLabel;

        SVGPushButton* prevButton;
        SVGPushButton* nextButton;

        SVGPushButton* closeButton;
};
