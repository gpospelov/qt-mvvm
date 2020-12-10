// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mainwindow.h"
#include "graphmodel.h"
#include "graphwidget.h"
#include <QCoreApplication>
#include <QSettings>
#include <QTabWidget>

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

namespace PlotGraphs
{

MainWindow::MainWindow()
    : m_tabWidget(new QTabWidget), m_graph_model(std::make_unique<GraphModel>())
{
    m_tabWidget->addTab(new GraphWidget(m_graph_model.get()), "Graphs");

    m_tabWidget->setCurrentIndex(m_tabWidget->count() - 1);
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
    QCoreApplication::setApplicationName("plotgraphs");
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

} // namespace PlotGraphs
