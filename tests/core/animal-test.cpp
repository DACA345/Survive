#include <gtest/gtest.h>
#include <Core/Animal.h>

TEST(AnimalTests, ConstrcutorJSONTest)
{
    // Test getting a random bird
    Animal animal("data/levels/mtaspiring/animals.json");

    QString randomBird = animal.getRandomBird();
    std::cout << "Random Bird: " << randomBird.toStdString() << std::endl;

    // Test getting a random mammal
    QString randomMammal = animal.getRandomMammal();
    std::cout << "Random Mammal: " << randomMammal.toStdString() << std::endl;

    // Test getting a random fish
    QString randomFish = animal.getRandomFish();
    std::cout << "Random Fish: " << randomFish.toStdString() << std::endl;

    // Test getting a random reptile
    QString randomReptile = animal.getRandomReptile();
    std::cout << "Random Reptile: " << randomReptile.toStdString() << std::endl;

    // Test getting a random amphibian
    QString randomAmphibian = animal.getRandomAmphibian();
    std::cout << "Random Amphibian: " << randomAmphibian.toStdString() << std::endl;

}