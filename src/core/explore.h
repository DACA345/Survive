#include <QString>
#include <QVector>
#include <QMap>

class Explore
{
public:
    // Constructor to initialize animals from JSON file
    Explore(const QString& filePath);

    // Load animal data from JSON file
    void loadActionsFromJson(const QString& filePath);

    // Get random animal from category as input
    QString getRandomExplores(const QString& category) const;

private:
    // Store animals categorized by species
    QMap<QString, QVector<QString>> explores;
};
