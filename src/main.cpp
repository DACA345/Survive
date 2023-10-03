#include <QApplication>

#include "survivegame.h"
#include "config/files.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setOrganizationName("DACA");
    QCoreApplication::setApplicationName("Survive");
    QCoreApplication::setApplicationVersion(VERSION);

    QApplication app(argc, argv);

#ifdef Q_OS_UNIX
    app.setWindowIcon(QIcon(TEXTURE_FILE("icon/icon.png")));
#endif

    SurviveGame game;

    game.show();

    return app.exec();
}