#include <gtest/gtest.h>
#include <Core/Event.h>

TEST(eventTest, JSONConstructorTest)
{
	Event disasters("data/levels/mtaspiring/disaster_ev.json");

	// Print each disaster details
	disasters.printAllEvents();

	disasters.printRandomEvent();
}