#include <QApplication>

#include "SurviveGame.h"
#include "Config/Files.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setOrganizationName("DACA");
    QCoreApplication::setApplicationName("Survive");
    QCoreApplication::setApplicationVersion(VERSION);

    QApplication app(argc, argv);

    SurviveGame game;

    game.show();

    return app.exec();
}