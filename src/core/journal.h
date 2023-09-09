#pragma once

#include <QMap>

struct ActionEntry
{
    QString action;
    QString result;
};

typedef QList<ActionEntry> DayEntries;

struct DayEntry
{
    QString dayEvent;
    DayEntries entries;
};


class Journal
{
    public:
        Journal();
        ~Journal();

        void addDay(int day, const QString& dayEvent = "There was no start of day event.");
        void addEntry(int day, ActionEntry entry);

        int getDayCount() const;
        const DayEntry& getEntry(int day) const;

    private:
        QMap<int, DayEntry> entries;
};
