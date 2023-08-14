#include <gtest/gtest.h>
#include <core/event.h>

TEST(EventTest, JSONConstructorTest)
{
	Event disasters("data/levels/mtaspiring/disaster_ev.json");

	// Print each disaster details
	disasters.printAllEvents();

	disasters.printRandomEvent();
}