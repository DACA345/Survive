#include <QString>
#include <QMap>

class Action {
public:
    // Constructor
    Action(const QString& filePath);

    // Load method
    void loadActionsFromJson(const QString& filePath);

    // Print method
    void printAllActions() const;

    // Get random method 
    QString getRandomAction() const;

    // Print random method
    void printRandomAction() const;

private:
    QMap<QString, QString> actions;
};