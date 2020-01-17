// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mainwindow.h"
#include "ApplicationModels.h"
#include <QAction>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QSettings>
#include <QTabWidget>

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

MainWindow::MainWindow()
    : m_tabWidget(new QTabWidget), m_models(std::make_unique<ApplicationModels>())
{


    initApplication();
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMainWindow::closeEvent(event);
}

void MainWindow::initApplication()
{
    QCoreApplication::setApplicationName("qt-mvvm-example");
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
