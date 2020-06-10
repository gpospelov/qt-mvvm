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
#include "projecthandler.h"
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
    : m_sampleModel(std::make_unique<SampleModel>()), m_actionManager(new ActionManager(this)),
      m_projectHandler(new ProjectHandler(m_sampleModel.get(), this))

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

    table_widget->setModel(m_sampleModel.get(), ModelView::Utils::TopItem(m_sampleModel.get()));
}

//! Setup main connections.

void MainWindow::init_connections()
{
    connect(m_actionManager, &ActionManager::createNewProjectRequest, m_projectHandler,
            &ProjectHandler::onCreateNewProject);
    connect(m_actionManager, &ActionManager::openExistingProjectRequest, m_projectHandler,
            &ProjectHandler::onOpenExistingProject);
    connect(m_actionManager, &ActionManager::saveCurrentProjectRequest, m_projectHandler,
            &ProjectHandler::onSaveCurrentProject);
    connect(m_actionManager, &ActionManager::saveProjectAsRequest, m_projectHandler,
            &ProjectHandler::onSaveProjectAs);
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.beginGroup(main_window_group);
    settings.setValue(size_key, size());
    settings.setValue(pos_key, pos());
    settings.endGroup();
}
