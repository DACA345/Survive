#include <gtest/gtest.h>
#include <core/journal.h>

TEST(JournalTest, addDayTest) 
{
	Journal testJournal;
	testJournal.addDay(1);

	EXPECT_EQ(testJournal.getDayCount(), 1);

}

TEST(JournalTest, addEntryTest) 
{
    Journal testJournal;
    testJournal.addDay(1);  // Adding a day before adding an entry.
    testJournal.addDay(1); // Should warn

    // Create an ActionEntry for testing.
    ActionEntry testEntry;
    testEntry.action = "Test Action";
    testEntry.result = "Test Result";  // Adding the result field.

    testJournal.addEntry(1, testEntry);

    // Retrieve the day entry and check if the added entry is present.
    DayEntry dayEntry = testJournal.getEntry(1);
    ASSERT_EQ(dayEntry.entries.size(), 1);

    // Check if the added entry matches the expected values.
    EXPECT_EQ(dayEntry.entries[0].action, "Test Action");
    EXPECT_EQ(dayEntry.entries[0].result, "Test Result");  // Check the result field.
}

TEST(JournalTest, getEntryExistingDayTest)
{
    Journal testJournal;
    testJournal.addDay(1);  // Adding a day before testing.

    // Create an ActionEntry for testing.
    ActionEntry testEntry;
    testEntry.action = "Test Action";
    testEntry.result = "Test Result";

    testJournal.addEntry(1, testEntry);
    testJournal.addEntry(2, testEntry); // Should warn

    // Retrieve the day entry and check if it exists.
    DayEntry dayEntry = testJournal.getEntry(1);

    // Check if the retrieved entry matches the expected values.
    EXPECT_EQ(dayEntry.entries.size(), 1);
    EXPECT_EQ(dayEntry.entries[0].action, "Test Action");
    EXPECT_EQ(dayEntry.entries[0].result, "Test Result");
}

TEST(JournalTest, getEntryNonExistingDayTest)
{
    Journal testJournal;

    // Try to retrieve an entry for a non-existing day.
    DayEntry dayEntry = testJournal.getEntry(1);

    // Check if the returned dayEntry is empty.
    EXPECT_EQ(dayEntry.entries.size(), 0);
}