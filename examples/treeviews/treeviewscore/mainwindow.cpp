// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mainwindow.h"
#include "sampleeditorwidget.h"
#include "samplemodel.h"
#include <QCoreApplication>
#include <QSettings>
#include <QTabWidget>

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

namespace TreeViews
{

MainWindow::MainWindow() : m_sample_model(std::make_unique<SampleModel>())
{
    auto central_widget = new SampleEditorWdiget(m_sample_model.get());
    setCentralWidget(central_widget);
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
    QCoreApplication::setApplicationName("treeviews");
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

} // namespace TreeViews
