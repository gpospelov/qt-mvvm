// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mainwindow.h"
#include "refldockwindow.h"
#include <QAction>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QSettings>
#include "mainbarwidget.h"

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

MainWindow::MainWindow() : m_reflDockWindow(new ReflDockWindow), bar_widget(new MainBarWidget)
{
    init_application();
    init_tabs();
    setCentralWidget(bar_widget);
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent* event)
{
    write_settings();
    QMainWindow::closeEvent(event);
}

void MainWindow::init_application()
{
    QCoreApplication::setApplicationName("quickrefl");
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

void MainWindow::init_tabs()
{
    bar_widget->addWidget(new QWidget, "Project");
    bar_widget->addWidget(new QWidget, "Data");
    bar_widget->addWidget(m_reflDockWindow, "Simulation");
    bar_widget->addWidget(new QWidget, "Fitting");
    bar_widget->addWidget(new QWidget, "Export");
    bar_widget->addWidget(new QWidget, "Settings");
    bar_widget->setCurrentIndex(2);
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.beginGroup(main_window_group);
    settings.setValue(size_key, size());
    settings.setValue(pos_key, pos());
    settings.endGroup();
}
