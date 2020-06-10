// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mainwindow.h"
#include "actionmanager.h"
#include "containereditorwidget.h"
#include "recentprojectmanager.h"
#include "recentprojectwidget.h"
#include "samplemodel.h"
#include <QCloseEvent>
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QSettings>
#include <mvvm/model/modelutils.h>

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

MainWindow::MainWindow()
    : m_actionManager(new ActionManager(this)),
      m_recentProjectManager(new RecentProjectManager(this)),
      m_sample_model(std::make_unique<SampleModel>())
{
    init_application();
    init_widgets();
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent* event)
{
    write_settings();
    QMainWindow::closeEvent(event);
}

void MainWindow::init_application()
{
    QCoreApplication::setApplicationName("saveloadproject");
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

void MainWindow::init_widgets()
{
    auto central_widget = new QWidget;
    auto central_layout = new QHBoxLayout(central_widget);

    auto project_widget = new RecentProjectWidget;
    auto table_widget = new ContainerEditorWidget;
    central_layout->addWidget(project_widget);
    central_layout->addWidget(table_widget);

    setCentralWidget(central_widget);

    table_widget->setModel(m_sample_model.get(), ModelView::Utils::TopItem(m_sample_model.get()));
}

//! Setup main connections.

void MainWindow::init_connections()
{
    connect(m_actionManager, &ActionManager::createNewProjectRequest, m_recentProjectManager,
            &RecentProjectManager::onCreateNewProject);
    connect(m_actionManager, &ActionManager::openExistingProjectRequest, m_recentProjectManager,
            &RecentProjectManager::onOpenExistingProject);
    connect(m_actionManager, &ActionManager::saveCurrentProjectRequest, m_recentProjectManager,
            &RecentProjectManager::onSaveCurrentProject);
    connect(m_actionManager, &ActionManager::saveProjectAsRequest, m_recentProjectManager,
            &RecentProjectManager::onSaveProjectAs);
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.beginGroup(main_window_group);
    settings.setValue(size_key, size());
    settings.setValue(pos_key, pos());
    settings.endGroup();
}
