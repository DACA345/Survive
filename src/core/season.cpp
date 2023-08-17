#include "season.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Season::Season(const QString& filename) 
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) 
    {
        qWarning("Couldn't open season file.");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject root = doc.object();

    for (auto it = root.begin(); it != root.end(); ++it) 
    {
        QString season = it.key();
        QJsonArray monthsArray = it.value().toArray();
        for (const QJsonValue& monthValue : monthsArray) {
            monthToSeason[monthValue.toString()] = season;
        }
    }
}

QString Season::getSeason(const QString& month) const
{
    auto it = monthToSeason.find(month);
    if (it != monthToSeason.end())
    {
        return it.value();
    }
    return "No seasons found";
}

QStringList Season::getMonth(const QString& season) const
{
    QStringList months;

    for (auto it = monthToSeason.begin(); it != monthToSeason.end(); ++it)
    {
        if (it.value() == season)
        {
            months << it.key();
        }
    }

    return months;
}
 