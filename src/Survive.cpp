#include <QCoreApplication>

int main(int argc, char** argv)
{
    QCoreApplication::setOrganizationName("DACA");

    QCoreApplication app(argc, argv);

    return app.exec();
}