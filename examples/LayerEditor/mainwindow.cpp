// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "mainwindow.h"
#include <QTabWidget>
#include <QCoreApplication>
#include <QSettings>

namespace {
    const QString main_window_group = "MainWindow";
    const QString size_key = "size";
    const QString pos_key = "pos";
}

MainWindow::MainWindow()
    : m_tabWidget(new QTabWidget)
{
    init_application();

}

void MainWindow::init_application()
{
    QCoreApplication::setApplicationName("layer-editor");
    QCoreApplication::setApplicationVersion("0.0");
    QCoreApplication::setOrganizationName("qt-mvvm");
    resize(1600, 1600);
}
