#include <QApplication>
#include <QScreen>

#include "SurviveGame.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setOrganizationName("DACA");
    QCoreApplication::setApplicationName("Survive");
    QCoreApplication::setApplicationVersion(VERSION);

    QApplication app(argc, argv);

    SurviveGame game;

    game.setMinimumSize(800, 600);
    game.show();

    return app.exec();
}