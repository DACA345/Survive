#include <gtest/gtest.h>
#include <core/event.h>

TEST(EventTest, JSONConstructorTest)
{
	Event event("data/levels/mtaspiring/disaster_ev.json");

	// Print each disaster details
	event.getEffect(event.getRandomEvent());

	QString randomEvent = event.getRandomEventForSeason("rawwing"); // Use a valid season name here
	EXPECT_TRUE(randomEvent.isEmpty()) << "No matching events found for the season";
}