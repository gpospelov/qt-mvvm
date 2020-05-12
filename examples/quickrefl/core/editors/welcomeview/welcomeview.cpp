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
#include "recentprojectwidget.h"
#include <QDebug>
#include <QHBoxLayout>

WelcomeView::WelcomeView(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_models(models), m_recent_project_widget(new RecentProjectWidget),
      m_open_project_widget(new OpenProjectWidget)
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

//! Returns directory on disk selected by the user via QFileDialog.
std::string WelcomeView::onSelectDirRequest()
{
    qDebug() << "WelcomeView::onSelectDirRequest()";
    return {};
}

//! Returns new directory on disk created by the user via QFileDialog.
std::string WelcomeView::onCreateDirRequest()
{
    qDebug() << "WelcomeView::onCreateDirRequest()";
    return {};
}

//! Returns save/cancel/discard changes choice provided by the user.
int WelcomeView::onSaveChangesRequest()
{
    qDebug() << "WelcomeView::onSaveChangesRequest()";
    return 0;
}

void WelcomeView::onCreateNewProject()
{
    qDebug() << "WelcomeView::onCreateNewProject()";
    m_project_manager->createNewProject();
}

void WelcomeView::onOpenExistingProject()
{
    qDebug() << "WelcomeView::onOpenExistingProject()";
    m_project_manager->openExistingProject();
}

void WelcomeView::onSaveCurrentProject()
{
    qDebug() << "WelcomeView::onSaveCurrentProject()";
    m_project_manager->saveCurrentProject();
}

void WelcomeView::init_project_manager()
{
    auto select_dir = [this]() { return onSelectDirRequest(); };
    auto create_dir = [this]() { return onCreateDirRequest(); };
    auto save_changes = [this]() {
        return static_cast<ProjectManagerDecorator::SaveChangesAnswer>(onSaveChangesRequest());
    };

    auto manager = std::make_unique<ProjectManagerDecorator>(m_models, select_dir, create_dir);
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
