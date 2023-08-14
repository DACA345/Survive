#include <QApplication>

#include "survivegame.h"
#include "config/files.h"

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