// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "welcomeviewsettings.h"
#include <QDir>
#include <QSettings>
#include <mvvm/utils/fileutils.h>

namespace
{
const int max_recent_projects = 10;

const QString group_key = "welcomeview";
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

WelcomeViewSettings::WelcomeViewSettings()
{
    readSettings();
}

WelcomeViewSettings::~WelcomeViewSettings()
{
    writeSettings();
}

//! Returns current workdir.
QString WelcomeViewSettings::currentWorkdir() const
{
    return m_current_workdir;
}

//! Updates current workdir value from user selection.
//! Workdir will be set as parent director of selected `dirname`.
void WelcomeViewSettings::updateWorkdirFromSelection(const QString& dirname)
{
    if (!dirname.isEmpty()) {
        auto parent_path = ModelView::Utils::parent_path(dirname.toStdString());
        m_current_workdir = QString::fromStdString(parent_path);
    }
}

//! Returns list of recent projects, validates if projects still exists on disk.
QStringList WelcomeViewSettings::recentProjects()
{
    QStringList updatedList;
    for (QString fileName : m_recent_projects) {
        QFile fin(fileName);
        if (fin.exists())
            updatedList.append(fileName);
    }
    m_recent_projects = updatedList;
    return m_recent_projects;
}

//! Adds directory to the list of recent projects.
void WelcomeViewSettings::addToRecentProjects(const QString& dirname)
{
    m_recent_projects.removeAll(dirname);
    m_recent_projects.prepend(dirname);
    while (m_recent_projects.size() > max_recent_projects)
        m_recent_projects.removeLast();
}

//! Write all settings to file.
void WelcomeViewSettings::writeSettings()
{
    QSettings settings;
    settings.setValue(workdir_setting_name(), m_current_workdir);
    settings.setValue(recent_projects_setting_name(), m_recent_projects);
}

//! Reads all settings from file.
void WelcomeViewSettings::readSettings()
{
    QSettings settings;
    m_current_workdir = QDir::homePath();

    if (settings.contains(workdir_setting_name()))
        m_current_workdir = settings.value(workdir_setting_name()).toString();

    if (settings.contains(recent_projects_setting_name()))
        m_recent_projects = settings.value(recent_projects_setting_name()).toStringList();
}
