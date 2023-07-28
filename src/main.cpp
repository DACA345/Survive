#include <QApplication>

#include "SurviveGame.h"
#include "Data.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setOrganizationName("DACA");
    QCoreApplication::setApplicationName("Survive");
    QCoreApplication::setApplicationVersion(VERSION);

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(TEXTURE_FILE("icon/icon.png")));

    qDebug() << TEXTURE_FOLDER;

    SurviveGame game;

    game.show();

    return app.exec();
}