#include <QApplication>
#include <QFile>
#include "MainWindow.h"
#include "PasswordManager.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    if (!QFile::exists("password.dat")) {
        PasswordManager::createDefaultAccount();
    }

    MainWindow w;
    w.show();
    return app.exec();

    return 0;
}