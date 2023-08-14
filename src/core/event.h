#include <QString>
#include <QMap>

class Event {
public:
    // Constructor
    Event(const QString& filePath);
    
    // Load method
    void loadEventsFromJson(const QString& filePath);

    // Print method
    void printAllEvents() const;

    // Get random method 
    QString getRandomEvent() const;

    // Print random method
    void printRandomEvent() const;

private:
    QMap<QString, QString> events;
};