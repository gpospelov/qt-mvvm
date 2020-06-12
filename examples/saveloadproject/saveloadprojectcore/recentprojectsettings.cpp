// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "recentprojectsettings.h"
#include <QDir>
#include <QSettings>
#include <mvvm/utils/fileutils.h>

namespace
{
const int max_recent_projects = 10;

const QString group_key = "recentproect";
const QString current_workdir_key = "currentworkdir";
const QString recent_projects_key = "recentprojects";

const QString workdir_setting_name()
{
    return group_key + "/" + current_workdir_key;
}

const QString recent_projects_setting_name()
{
    return group_key + "/" + recent_projects_key;
}

} // namespace

RecentProjectSettings::RecentProjectSettings()
{
    readSettings();
}

RecentProjectSettings::~RecentProjectSettings()
{
    writeSettings();
}

//! Returns current workdir.
QString RecentProjectSettings::currentWorkdir() const
{
    return m_currentWorkdir;
}

//! Updates current workdir value from user selection.
//! Workdir will be set as parent director of selected `dirname`.
void RecentProjectSettings::updateWorkdirFromSelection(const QString& dirname)
{
    if (!dirname.isEmpty()) {
        auto parent_path = ModelView::Utils::parent_path(dirname.toStdString());
        m_currentWorkdir = QString::fromStdString(parent_path);
    }
}

//! Returns list of recent projects, validates if projects still exists on disk.
QStringList RecentProjectSettings::recentProjects()
{
    QStringList updatedList;
    for (const auto& fileName : m_recentProjects) {
        if (ModelView::Utils::exists(fileName.toStdString()))
            updatedList.append(fileName);
    }
    m_recentProjects = updatedList;
    return m_recentProjects;
}

//! Adds directory to the list of recent projects.
void RecentProjectSettings::addToRecentProjects(const QString& dirname)
{
    m_recentProjects.removeAll(dirname);
    m_recentProjects.prepend(dirname);
    while (m_recentProjects.size() > max_recent_projects)
        m_recentProjects.removeLast();
}

//! Write all settings to file.
void RecentProjectSettings::writeSettings()
{
    QSettings settings;
    settings.setValue(workdir_setting_name(), m_currentWorkdir);
    settings.setValue(recent_projects_setting_name(), m_recentProjects);
}

//! Reads all settings from file.
void RecentProjectSettings::readSettings()
{
    QSettings settings;
    m_currentWorkdir = QDir::homePath();

    if (settings.contains(workdir_setting_name()))
        m_currentWorkdir = settings.value(workdir_setting_name()).toString();

    if (settings.contains(recent_projects_setting_name()))
        m_recentProjects = settings.value(recent_projects_setting_name()).toStringList();
}
