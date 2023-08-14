#include <gtest/gtest.h>
#include <core/animal.h>

TEST(AnimalTest, MethodConstructorTest)
{
    // Test getting a random bird
    Animal animal("data/levels/mtaspiring/animals.json");

    QString randomAnimal = animal.getRandomAnimal("birds");
    std::cout << "Random animal: " << randomAnimal.toStdString() << std::endl;

}