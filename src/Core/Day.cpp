#include "Day.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

void Day::loadClimateData(const std::string& filename) {
    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject j = doc.object();

    for (auto it = j.begin(); it != j.end(); ++it) {
        std::vector<ClimateData> monthData;
        QJsonArray monthArray = it.value().toArray();
        for (auto val : monthArray) {
            QJsonObject monthElement = val.toObject();
            ClimateData cd;
            cd.max_temperature.max = monthElement["max_temperature"]["max"].toDouble();
            cd.max_temperature.average = monthElement["max_temperature"]["average"].toDouble();
            cd.max_temperature.min = monthElement["max_temperature"]["min"].toDouble();

            cd.avg_temperature.max = monthElement["avg_temperature"]["max"].toDouble();
            cd.avg_temperature.average = monthElement["avg_temperature"]["average"].toDouble();
            cd.avg_temperature.min = monthElement["avg_temperature"]["min"].toDouble();

            cd.min_temperature.max = monthElement["min_temperature"]["max"].toDouble();
            cd.min_temperature.average = monthElement["min_temperature"]["average"].toDouble();
            cd.min_temperature.min = monthElement["min_temperature"]["min"].toDouble();

            cd.precipitation.max = monthElement["precipitation"]["max"].toDouble();
            cd.precipitation.average = monthElement["precipitation"]["average"].toDouble();
            cd.precipitation.min = monthElement["precipitation"]["min"].toDouble();
            cd.precipitation.sum = monthElement["precipitation"]["sum"].toDouble();

            cd.snow_depth.max = monthElement["snowdepth"]["max"].toDouble();
            cd.snow_depth.average = monthElement["snowdepth"]["average"].toDouble();
            cd.snow_depth.min = monthElement["snowdepth"]["min"].toDouble();
            cd.snow_depth.sum = monthElement["snowdepth"]["sum"].toDouble();

            monthData.push_back(cd);
        }
        climateData[it.key().toStdString()] = monthData;
    }
}
