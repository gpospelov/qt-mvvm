// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "recentprojectmanager.h"
#include "recentprojectsettings.h"
#include "userinteractor.h"
#include <mvvm/project/projectmanagerdecorator.h>

using namespace ModelView;

RecentProjectManager::RecentProjectManager(QObject* parent)
    : QObject(parent), m_recentProjectSettings(std::make_unique<RecentProjectSettings>()),
      m_userInteractor(std::unique_ptr<UserInteractor>())
{
    init_project_manager();
}

RecentProjectManager::~RecentProjectManager() = default;

void RecentProjectManager::onCreateNewProject() {}

void RecentProjectManager::onOpenExistingProject(const QString& dirname) {}

void RecentProjectManager::onSaveCurrentProject() {}

void RecentProjectManager::onSaveProjectAs() {}

void RecentProjectManager::init_project_manager()
{
    auto select_dir = [this]() { return m_userInteractor->onSelectDirRequest(); };
    auto create_dir = [this]() { return m_userInteractor->onCreateDirRequest(); };
    auto save_changes = [this]() { return m_userInteractor->onSaveChangesRequest(); };
    auto on_modified = [this]() { update_current_project_name(); };

//    auto manager =
//        std::make_unique<ProjectManagerDecorator>(m_model, select_dir, create_dir, on_modified);
//    manager->setSaveChangesAnswerCallback(save_changes);

//    m_projectManager = std::move(manager);
}

void RecentProjectManager::update_current_project_name()
{

}

void RecentProjectManager::update_recent_project_names()
{

}
