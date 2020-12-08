// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mainwindow.h"
#include "item_constants.h"
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

namespace CellEditors
{

MainWindow::MainWindow() : m_tabWidget(new QTabWidget), m_model(std::make_unique<SampleModel>())
{
    setCentralWidget(m_tabWidget);
    init_application();
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
    QCoreApplication::setApplicationName("celleditors");
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("qt-mvvm");

    QSettings settings;
    if (settings.childGroups().contains(main_window_group)) {
        settings.beginGroup(main_window_group);
        resize(settings.value(size_key, QSize(400, 400)).toSize());
        move(settings.value(pos_key, QPoint(200, 200)).toPoint());
        settings.endGroup();
    }

    init_models();
}

void MainWindow::init_models()
{
    // populating first model with content
    m_model->insertItem<DemoPropertiesItem>();
    m_model->insertItem<DemoPropertiesItem>();
    m_model->insertItem<DemoPropertiesItem>();

    m_tabWidget->addTab(new ModelEditorWidget(m_model.get()), "Available properties");
    m_tabWidget->setCurrentIndex(m_tabWidget->count() - 1);
}

} // namespace CellEditors
