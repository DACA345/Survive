#include <QString>
#include <QVector>
#include <QMap>

class Animal {
public:
    // Constructor to initialize animals from JSON file
    Animal(const QString& filePath);

    // Load animal data from JSON file
    void loadAnimalsFromJson(const QString& filePath);

    // Get random animal from category as input
    QString getRandomAnimal(const QString& category) const;

private:
    // Store animals categorized by species
    QMap<QString, QVector<QString>> animals;
};





