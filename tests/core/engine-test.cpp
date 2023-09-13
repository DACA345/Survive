#include <gtest/gtest.h>
#include <core/engine.h>

#define SEED 1

TEST(EngineTests, ConstructorTest)
{
    Engine test = Engine("mtaspiring", SEED);

    // Check seeding
    EXPECT_EQ(test.probability(), 0.55794434812820504);
    EXPECT_EQ(test.probability(), 0.69514689564344823);
}

TEST(EngineTests, GetTest)
{
    Engine test = Engine("mtaspiring", SEED);

    const Level& level = test.getLevel();
    const Day& day = test.getDay();
    const Journal& journal = test.getJournal();

    // Check level
    EXPECT_NO_THROW(level.getAnimals().getRandomAnimal());
    EXPECT_NE(level.getAnimals().getRandomAnimal().name, "");

    EXPECT_NO_THROW(level.getEvents().getRandomEvent());
    EXPECT_NE(level.getEvents().getRandomEvent().event, "");

    EXPECT_NO_THROW(level.getPlants().getRandomPlant());
    EXPECT_NE(level.getPlants().getRandomPlant().name, "");

    // Check day
    EXPECT_EQ(day.currentDay(), 1);

    // Check journal
    EXPECT_EQ(journal.getDayCount(), 1);
}

TEST(EngineTests, DayTest)
{
    Engine test = Engine("mtaspiring", SEED);

    // Check bars start at BAR_MAX
    EXPECT_EQ(test.getHealth(), BAR_MAX);
    EXPECT_EQ(test.getHunger(), BAR_MAX);
    EXPECT_EQ(test.getThirst(), BAR_MAX);
    EXPECT_EQ(test.getEnergy(), BAR_MAX);

    EXPECT_NO_THROW(test.findFood());
    EXPECT_NO_THROW(test.findWater());
    EXPECT_NO_THROW(test.explore());
    EXPECT_NO_THROW(test.rest());

    // Check bars have updated
    EXPECT_EQ(test.getHunger(), 60);
    EXPECT_EQ(test.getThirst(), 60);
    EXPECT_EQ(test.getEnergy(), 50);

    EXPECT_FALSE(test.isGameOver());
}