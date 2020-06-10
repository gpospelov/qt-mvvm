// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "welcomeview.h"
#include "applicationmodels.h"
#include "openprojectwidget.h"
#include <mvvm/project/projectmanagerdecorator.h>
#include "projectmanagerinteractor.h"
#include <mvvm/project/projectutils.h>
#include "recentprojectwidget.h"
#include "welcomeviewsettings.h"
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMainWindow>
#include <mvvm/widgets/widgetutils.h>

WelcomeView::WelcomeView(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_models(models), m_recent_project_widget(new RecentProjectWidget),
      m_open_project_widget(new OpenProjectWidget),
      m_settings(std::make_unique<WelcomeViewSettings>()),
      m_interactor(std::make_unique<ProjectManagerInteractor>(this, m_settings.get()))
{
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(palette);

    auto layout = new QHBoxLayout(this);
    layout->addSpacing(50);
    layout->addWidget(m_recent_project_widget);
    layout->addWidget(m_open_project_widget);
    layout->addSpacing(50);

    init_project_manager();
    setup_connections();
    update_recent_project_names();
}

WelcomeView::~WelcomeView() = default;

//! Returns 'true' if current project can be closed.
//! Internally will perform check for unsaved data, and proceed via save/discard/cancel dialog.

bool WelcomeView::canCloseProject() const
{
    return m_project_manager->closeCurrentProject();
}

void WelcomeView::onCreateNewProject()
{
    qDebug() << "WelcomeView::onCreateNewProject()";
    if (m_project_manager->createNewProject()) {
        update_current_project_name();
        update_recent_project_names();
    }
}

void WelcomeView::onOpenExistingProject(const QString& dirname)
{
    qDebug() << "WelcomeView::onOpenExistingProject()" << dirname;
    if (m_project_manager->openExistingProject(dirname.toStdString())) {
        update_current_project_name();
        update_recent_project_names();
    }
}

void WelcomeView::onSaveCurrentProject()
{
    qDebug() << "WelcomeView::onSaveCurrentProject()";
    if (m_project_manager->saveCurrentProject()) {
        update_current_project_name();
        update_recent_project_names();
    }
}

void WelcomeView::onSaveProjectAs()
{
    qDebug() << "WelcomeView::onSaveProjectAs()";
    if (m_project_manager->saveProjectAs()) {
        update_current_project_name();
        update_recent_project_names();
    }
}

void WelcomeView::init_project_manager()
{
    auto select_dir = [this]() { return m_interactor->onSelectDirRequest(); };
    auto create_dir = [this]() { return m_interactor->onCreateDirRequest(); };
    auto save_changes = [this]() { return m_interactor->onSaveChangesRequest(); };
    auto on_modified = [this]() { update_current_project_name(); };

    auto manager =
        std::make_unique<ProjectManagerDecorator>(m_models, select_dir, create_dir, on_modified);
    manager->setSaveChangesAnswerCallback(save_changes);

    m_project_manager = std::move(manager);
}

void WelcomeView::setup_connections()
{
    auto open_existing_project = [this]() { onOpenExistingProject(); };
    connect(m_open_project_widget, &OpenProjectWidget::openExistingProjectRequest,
            open_existing_project);
    connect(m_open_project_widget, &OpenProjectWidget::createNewProjectRequest, this,
            &WelcomeView::onCreateNewProject);
    connect(m_open_project_widget, &OpenProjectWidget::saveProjectRequest, this,
            &WelcomeView::onSaveCurrentProject);
    connect(m_open_project_widget, &OpenProjectWidget::saveProjectAsRequest, this,
            &WelcomeView::onSaveProjectAs);
    connect(m_recent_project_widget, &RecentProjectWidget::projectSelected, this,
            &WelcomeView::onOpenExistingProject);
}

//! Sets changed project name to all widgets which requires it.

void WelcomeView::update_current_project_name()
{
    const auto current_project_dir = QString::fromStdString(m_project_manager->currentProjectDir());
    const auto is_modified = m_project_manager->isModified();

    auto title = ModelView::Utils::ProjectWindowTitle(current_project_dir, is_modified);
    if (auto main_window = ModelView::Utils::FindMainWindow(); main_window)
        main_window->setWindowTitle(title);

    m_recent_project_widget->setCurrentProject(current_project_dir, is_modified);
}

//! Update all panes with titles and project dir for all recent projetcs.

void WelcomeView::update_recent_project_names()
{
    m_settings->addToRecentProjects(QString::fromStdString(m_project_manager->currentProjectDir()));
    m_recent_project_widget->setRecentProjectsList(m_settings->recentProjects());
}
