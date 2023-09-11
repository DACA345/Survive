#include <gtest/gtest.h>
#include <core/event.h>

TEST(EventTest, JSONConstructorTest)
{
    
    // Create an instance of the Event class with a test JSON file
    Event event("data/levels/mtaspiring/events.json");

    // Test the constructor
    EXPECT_NO_THROW(Event("data/levels/mtaspiring/events.json"));

    const EventInfo randomEvent = event.getRandomEvent();
    EXPECT_FALSE(randomEvent.event.isEmpty());
    EXPECT_TRUE(randomEvent.effect.energyBar != NULL);
    EXPECT_TRUE(randomEvent.effect.healthBar != NULL);
    EXPECT_TRUE(randomEvent.effect.hungerBar != NULL);
    EXPECT_TRUE(randomEvent.effect.moraleBar != NULL);
    EXPECT_TRUE(randomEvent.effect.thirstBar != NULL);

}