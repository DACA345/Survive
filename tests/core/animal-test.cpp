#include <gtest/gtest.h>
#include <Core/Animal.h>

TEST(AnimalTests, MethodConstructorTest)
{
    // Test getting a random bird
    Animal animal("data/levels/mtaspiring/animals.json");

    QString randomAnimal = animal.getRandomAnimal("mammals");
    std::cout << "Random animal: " << randomAnimal.toStdString() << std::endl;

}