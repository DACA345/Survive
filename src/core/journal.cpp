#include "journal.h"

Journal::Journal()
{
}

void Journal::addDay(int day, const QString& dayEvent)
{
    if (entries.contains(day))
    {
        qWarning("Journal::addDay: Day %d already exists", day);
        return;
    }

    entries[day] = DayEntry{ dayEvent, DayEntries() };
}

void Journal::addEntry(int day, ActionEntry entry)
{
    if (!entries.contains(day))
    {
        qWarning("Journal::addEntry: Day %d does not exist", day);
        return;
    }

    entries[day].entries.append(entry);
}

int Journal::getDayCount() const
{
    return entries.size();
}

DayEntry Journal::getEntry(int day) const
{
    if (!entries.contains(day))
    {
        qWarning("Journal::getEntries: Day %d does not exist", day);
        return DayEntry();
    }

    return entries[day];
}

Journal::~Journal()
{
}
