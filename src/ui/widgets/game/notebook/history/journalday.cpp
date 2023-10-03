#include "journalday.h"

#include <QPalette>

JournalDay::JournalDay(const DayEntry& day, QWidget *parent)
    : ScalableWidget(parent)
{
    setupUi(day);
}

void JournalDay::setupUi(const DayEntry& day)
{
    dayEventLabel = new ScalableLabel(day.dayEvent, this);
    dayEventLabel->setAlignment(Qt::AlignCenter);

    addWidget(dayEventLabel, 0, 0, 1, 0.1);

    if (day.entries.size() == 0)
    {
        return;
    }

    for (const ActionEntry& action : day.entries)
    {
        ScalableLabel* actionLabel = new ScalableLabel(QString("<b>%1</b>").arg(action.action), this);
        actionLabel->setAlignment(Qt::AlignCenter);
        dayActions.append(actionLabel);

        ScalableLabel* resultLabel = new ScalableLabel(action.result, this);
        resultLabel->setAlignment(Qt::AlignCenter);
        dayResults.append(resultLabel);
    }

    for (int i = 0; i < dayActions.size(); i++)
    {
        addWidget(dayActions[i], 0.05, 0.125 + (i * 0.125), 0.9, 0.075);
        addWidget(dayResults[i], 0.05, 0.175 + (i * 0.125), 0.9, 0.075);
    }
}

JournalDay::~JournalDay()
{

}
