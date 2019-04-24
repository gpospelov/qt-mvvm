// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "mainwindow.h"
#include "testwidget1.h"
#include "ApplicationModels.h"
#include <QTabWidget>
#include <QCoreApplication>
#include <QSettings>

namespace {
    const QString main_window_group = "MainWindow";
    const QString size_key = "size";
    const QString pos_key = "pos";
}

MainWindow::MainWindow()
    : m_tabWidget(new QTabWidget), m_models(std::make_unique<ApplicationModels>())
{    
    m_tabWidget->addTab(new TestWidget1(m_models.get()), "Model basics");

    m_tabWidget->setCurrentIndex(m_tabWidget->count()-1);
    setCentralWidget(m_tabWidget);

    init_application();
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent* event)
{
    write_settings();
    QMainWindow::closeEvent(event);
}

void MainWindow::init_application()
{
    QCoreApplication::setApplicationName("qt-mvvm-miniba");
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("qt-mvvm");

    QSettings settings;
    if (settings.childGroups().contains(main_window_group)) {
        settings.beginGroup(main_window_group);
        resize(settings.value(size_key, QSize(400, 400)).toSize());
        move(settings.value(pos_key, QPoint(200, 200)).toPoint());
        settings.endGroup();
    }
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.beginGroup(main_window_group);
    settings.setValue(size_key, size());
    settings.setValue(pos_key, pos());
    settings.endGroup();
}
