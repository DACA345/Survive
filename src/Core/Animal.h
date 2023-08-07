#include <QString>
#include <QVector>
#include <QMap>

class Animal {
public:
    // Constructor to initialize animals from JSON file
    Animal(const QString& filePath);

    // Load animal data from JSON file
    void loadAnimalsFromJson(const QString& filePath);

    // Get a random animal from each category
    QString getRandomBird() const;
    QString getRandomMammal() const;
    QString getRandomFish() const;
    QString getRandomReptile() const;
    QString getRandomAmphibian() const;

private:
    // Store animals categorized by species
    QMap<QString, QVector<QString>> animals;
};





