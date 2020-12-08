// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mainwindow.h"
#include "modeleditorwidget.h"
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

namespace DragAndView
{

MainWindow::MainWindow() : m_tabWidget(new QTabWidget), m_model(std::make_unique<SampleModel>())
{
    setCentralWidget(m_tabWidget);
    init_application();

    m_tabWidget->addTab(new ModelEditorWidget(m_model.get()), "Drag and Move");
    m_tabWidget->setCurrentIndex(m_tabWidget->count() - 1);
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent* event)
{
    write_settings();
    QMainWindow::closeEvent(event);
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.beginGroup(main_window_group);
    settings.setValue(size_key, size());
    settings.setValue(pos_key, pos());
    settings.endGroup();
}

void MainWindow::init_application()
{
    QCoreApplication::setApplicationName("dragandmove");
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

} // namespace DragAndView
