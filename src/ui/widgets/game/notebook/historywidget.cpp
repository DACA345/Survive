#include "historywidget.h"
#include "../../../../config/files.h"

HistoryWidget::HistoryWidget(const Journal& journal, int currentDay, QWidget *parent)
    : ScalableWidget(parent), journal(journal), currentDay(currentDay)
{
    setupUi();
}

void HistoryWidget::showDay(int day)
{
    removeWidget(journalDay);
    delete journalDay;

    dayLabel->setText(QString("Day %1").arg(day));

    journalDay = new JournalDay(journal.getEntry(day), this);
    currentDay = day;

    addWidget(journalDay, 0, 0.25, 1, 0.75);

    journalDay->show();

    closeButton->raise();
}

void HistoryWidget::setupUi()
{
    titleLabel = new ScalableLabel("Journal", this);
    titleLabel->setAlignment(Qt::AlignCenter);

    dayLabel = new ScalableLabel(QString("Day %1").arg(currentDay), this);
    dayLabel->setAlignment(Qt::AlignCenter);

    prevButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/left.svg"), this);
    nextButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/right.svg"), this);

    closeButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/okay.svg"), this);

    connect(prevButton, &QPushButton::clicked, this, [this]() {
        if (currentDay > 1)
        {
            showDay(currentDay - 1);
        }
    });

    connect(nextButton, &QPushButton::clicked, this, [this]() {
            if (currentDay < journal.getDayCount())
            {
                showDay(currentDay + 1);
            }
    });

    connect(closeButton, &QPushButton::clicked, this, &HistoryWidget::close);

    addWidget(titleLabel, 0, 0.1, 1, 0.1);

    addWidget(dayLabel, 0.375, 0.175, 0.25, 0.1);

    addWidget(prevButton, 0.275, 0.2, 0.1, 0.05);
    addWidget(nextButton, 0.625, 0.2, 0.1, 0.05);

    addWidget(closeButton, 0.8, 0.875, 0.15, 0.045);
}

HistoryWidget::~HistoryWidget()
{
    if (journalDay)
    {
        delete journalDay;
    }

    delete titleLabel;
    delete dayLabel;
    delete prevButton;
    delete nextButton;
    delete closeButton;
}
