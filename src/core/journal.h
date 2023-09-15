#pragma once

#include <QMap>

/**
 * @brief      Action details for the journal.
 */
struct ActionEntry
{
    QString action;
    QString result;
};

typedef QList<ActionEntry> DayEntries;

/**
 * @brief      Entry for a journal's day.
 */
struct DayEntry
{
    QString dayEvent;
    DayEntries entries;
};

/**
 * @brief      This class describes a journal for storing game events.
 */
class Journal
{
    public:
        /**
         * @brief      Constructs a new journal instance.
         */
        Journal();

        /**
         * @brief      Destroys the object.
         */
        ~Journal();

        /**
         * @brief      Adds a day to the journal.
         *
         * @param[in]  day       The day
         * @param[in]  dayEvent  The day event
         */
        void addDay(int day, const QString& dayEvent = "There was no start of day event.");

        /**
         * @brief      Adds an action entry to a day.
         *
         * @param[in]  day    The day
         * @param[in]  entry  The entry
         */
        void addEntry(int day, ActionEntry entry);

        /**
         * @brief      Gets the day count.
         *
         * @return     The day count.
         */
        int getDayCount() const;

        /**
         * @brief      Gets the entry for a given day.
         *
         * @param[in]  day   The day
         *
         * @return     The entry.
         */
        DayEntry getEntry(int day) const;

    private:
        /**
         * Maps the days to the journal entries.
         */
        QMap<int, DayEntry> entries;
};
