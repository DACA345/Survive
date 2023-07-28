#include <QApplication>

#include "SurviveGame.h"
#include "Files.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setOrganizationName("DACA");
    QCoreApplication::setApplicationName("Survive");
    QCoreApplication::setApplicationVersion(VERSION);

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(TEXTURE_FILE("icon/icon.png")));

    SurviveGame game;

    game.show();

    return app.exec();
}