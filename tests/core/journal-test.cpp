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