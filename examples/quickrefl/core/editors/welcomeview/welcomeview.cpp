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
#include "projectmanagerdecorator.h"
#include "projectmanagerinteractor.h"
#include "projectutils.h"
#include "recentprojectwidget.h"
#include "welcomeviewsettings.h"
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMainWindow>

namespace
{
QMainWindow* findMainWindow()
{
    for (auto widget : qApp->topLevelWidgets()) {
        if (auto result = dynamic_cast<QMainWindow*>(widget); result)
            return result;
    }
    return nullptr;
}
} // namespace

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
}

WelcomeView::~WelcomeView() = default;

void WelcomeView::onCreateNewProject()
{
    qDebug() << "WelcomeView::onCreateNewProject()";
    if (m_project_manager->createNewProject())
        update_current_project_name();
}

void WelcomeView::onOpenExistingProject()
{
    qDebug() << "WelcomeView::onOpenExistingProject()";
    if (m_project_manager->openExistingProject())
        update_current_project_name();
}

void WelcomeView::onSaveCurrentProject()
{
    qDebug() << "WelcomeView::onSaveCurrentProject()";
    if (m_project_manager->saveCurrentProject())
        update_current_project_name();
}

void WelcomeView::init_project_manager()
{
    auto select_dir = [this]() { return m_interactor->onSelectDirRequest(); };
    auto create_dir = [this]() { return m_interactor->onCreateDirRequest(); };
    auto save_changes = [this]() {
        return static_cast<ProjectManagerDecorator::SaveChangesAnswer>(
            m_interactor->onSaveChangesRequest());
    };
    auto on_modified = [this]() { update_current_project_name(); };

    auto manager =
        std::make_unique<ProjectManagerDecorator>(m_models, select_dir, create_dir, on_modified);
    manager->setSaveChangesAnswerCallback(save_changes);

    m_project_manager = std::move(manager);
}

void WelcomeView::setup_connections()
{
    connect(m_open_project_widget, &OpenProjectWidget::openExistingProjectRequest, this,
            &WelcomeView::onOpenExistingProject);
    connect(m_open_project_widget, &OpenProjectWidget::createNewProjectRequest, this,
            &WelcomeView::onCreateNewProject);
}

//! Sets changed project name to all widgets which requires it.

void WelcomeView::update_current_project_name()
{
    auto title = ProjectUtils::ProjectWindowTitle(m_project_manager->currentProjectDir(),
                                                  m_project_manager->isModified());
    if (auto main_window = findMainWindow(); main_window)
        main_window->setWindowTitle(QString::fromStdString(title));

    m_recent_project_widget->setCurrentProject(title, m_project_manager->currentProjectDir());
}
