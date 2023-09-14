#include <gtest/gtest.h>
#include <core/engine.h>

#define SEED 1

TEST(EngineTests, ConstructorTest)
{
    Engine test = Engine("mtaspiring", SEED);
    Engine copy = Engine(test);

    // Check seeding
    EXPECT_EQ(test.probability(), copy.probability());
    EXPECT_EQ(test.probability(), 0.69514689564344823);
    EXPECT_EQ(copy.probability(), 0.69514689564344823);

    Engine randomTest = Engine("mtaspiring");

    EXPECT_LT(test.probability(), 1);
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

    EXPECT_NO_THROW(level.getExplorer().getRandomExplore());
    EXPECT_NE(level.getExplorer().getRandomExplore().eventName, "");

    EXPECT_EQ(level.getInfo().name, "mtaspiring");

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
    EXPECT_NO_THROW(test.rest());
    EXPECT_NO_THROW(test.explore());

    EXPECT_EQ(test.getTurns(), 1);

    // Check bars have updated
    EXPECT_LT(test.getHunger(), BAR_MAX);
    EXPECT_LT(test.getThirst(), BAR_MAX);
    EXPECT_LT(test.getEnergy(), BAR_MAX);

    EXPECT_FALSE(test.isGameOver());

    test.nextDay();

    EXPECT_NO_THROW(test.explore());
    EXPECT_NO_THROW(test.explore());
    EXPECT_NO_THROW(test.explore());
    EXPECT_NO_THROW(test.explore());
    EXPECT_NO_THROW(test.explore());
}

TEST(EngineTests, NextDayTest)
{
    Engine test = Engine("mtaspiring", SEED);

    EXPECT_EQ(test.getDay().currentDay(), 1);

    EXPECT_NO_THROW(test.nextDay());

    EXPECT_EQ(test.getDay().currentDay(), 2);
}
