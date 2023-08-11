#include <gtest/gtest.h>
#include <Core/Event.h>

TEST(eventTest, JSONConstructorTest)
{
	Event disasters("C:/Users/Andrew John/Source/Repos/DACA345/Survive/tests/data/levels/mtaspiring/disaster_ev.json");

	// Print each disaster details
	disasters.printAllEvents();

	disasters.printRandomEvent();
}