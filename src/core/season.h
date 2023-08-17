#include <QString>
#include <QMap>

class Season {
public:
    Season(const QString& filename);

    QString getSeason(const QString& month) const;

    QStringList getMonth(const QString& season) const;

private:
    QMap<QString, QString> monthToSeason;
};
