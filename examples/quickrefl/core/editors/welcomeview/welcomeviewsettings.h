// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef WELCOMEVIEWSETTINGS_H
#define WELCOMEVIEWSETTINGS_H

#include <QString>
#include <QStringList>

//! Collection of settings for WelcomeView.
//! Used to save last directory selected by the user, and similar.
//! Relies on QSettings machinery.

class WelcomeViewSettings
{
public:
    WelcomeViewSettings();
    ~WelcomeViewSettings();

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

#endif // WELCOMEVIEWSETTINGS_H
