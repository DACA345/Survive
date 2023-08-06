#include <QString>
#include <QVector>

class Animal {
public:
    Animal(const QString& jsonFilePath);
    QString getSpeciesID() const;
    QString getName() const;
    QString getCategory() const;
    // Add other getter methods and query methods as needed.

private:
    struct AnimalData {
        QString speciesID;
        QString name;
    };

    QVector<AnimalData> birds;
    QVector<AnimalData> mammals;
    QVector<AnimalData> fishes;
    QVector<AnimalData> reptiles;
    QVector<AnimalData> amphibians;
};