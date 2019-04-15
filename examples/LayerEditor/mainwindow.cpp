// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "mainwindow.h"
#include "option1.h"
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
    m_tabWidget->addTab(new Option1Widget, "Layer editor v.1");

    m_tabWidget->setCurrentIndex(m_tabWidget->count()-1);
    setCentralWidget(m_tabWidget);

    init_application();
}

void MainWindow::init_application()
{
    QCoreApplication::setApplicationName("layer-editor");
    QCoreApplication::setApplicationVersion("0.0");
    QCoreApplication::setOrganizationName("qt-mvvm");
    resize(1600, 1600);
}
