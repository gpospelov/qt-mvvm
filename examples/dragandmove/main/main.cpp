#include "mainwindow.h"
#include <QApplication>
#include <QLocale>

int main(int argc, char **argv)
{
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    QApplication app(argc, argv);

    MainWindow win;
    win.show();

    return app.exec();
}
