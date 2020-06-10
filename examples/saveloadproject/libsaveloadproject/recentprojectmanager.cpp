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

RecentProjectManager::RecentProjectManager(QObject* parent)
    : QObject(parent), m_recentProjectSettings(std::make_unique<RecentProjectSettings>())
{
}

RecentProjectManager::~RecentProjectManager() = default;

void RecentProjectManager::onCreateNewProject()
{

}

void RecentProjectManager::onOpenExistingProject(const QString &dirname)
{

}

void RecentProjectManager::onSaveCurrentProject()
{

}

void RecentProjectManager::onSaveProjectAs()
{

}
