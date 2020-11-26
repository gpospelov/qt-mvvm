// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QApplication>
#include <QLocale>
#include <collidingmicecore/mainwindow.h>

void messageHandler(QtMsgType, const QMessageLogContext&, const QString&) {}

int main(int argc, char** argv)
{
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    QApplication app(argc, argv);
    qInstallMessageHandler(messageHandler);
    MainWindow win;
    win.show();

    return app.exec();
}
