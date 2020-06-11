// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef RECENTPROJECTSETTINGS_H
#define RECENTPROJECTSETTINGS_H

#include <QStringList>

//! Collection of settings for RecentProjectWidget. Used to save last directory selected
//! by the user, and list of recent projects. Relies on QSettings machinery.

class RecentProjectSettings
{
public:
    RecentProjectSettings();
    ~RecentProjectSettings();

    QString currentWorkdir() const;

    void updateWorkdirFromSelection(const QString& dirname);

    QStringList recentProjects();

    void addToRecentProjects(const QString& dirname);

private:
    void writeSettings();
    void readSettings();

    QString m_current_workdir;
    QStringList m_recent_projects;
};

#endif // RECENTPROJECTSETTINGS_H
